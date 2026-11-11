# 579. Find Cumulative Salary of an Employee

* **Link:** [LeetCode 579 – Find Cumulative Salary of an Employee](https://leetcode.com/problems/find-cumulative-salary-of-an-employee/)
* **Độ khó:** Hard
* **Chủ đề:** Window Function, CTE, Sliding Window, RANGE vs ROWS

---

## 1. Đề bài

Bảng `Employee` gồm các cột:

* `id`: Mã nhân viên.
* `month`: Tháng (1–12) trong năm 2020.
* `salary`: Mức lương của tháng đó.

Khóa chính: `(id, month)`. Mỗi dòng thể hiện lương của một nhân viên trong **một tháng cụ thể**. Nhân viên có thể **nghỉ một số tháng** — những tháng đó **không có dòng** trong bảng.

### Yêu cầu

Với **mỗi nhân viên**, tính **lương tích lũy 3 tháng** cho mỗi tháng có đi làm:

```text
Salary(month M) = salary(M) + salary(M-1) + salary(M-2)
```

Trong đó, **tháng không có ghi nhận lương được coi là 0**.

### Quy tắc loại trừ (quan trọng)

* **KHÔNG** trả về kết quả cho **tháng mới nhất** (`MAX(month)`) của mỗi nhân viên.
* **KHÔNG** trả về các tháng mà nhân viên **không đi làm** (không có dòng trong bảng).

### Sắp xếp kết quả

* `id` tăng dần.
* Trong cùng `id`, `month` **giảm dần**.

### Ví dụ

**Input (`Employee`):**

| id | month | salary |
| :--- | :--- | :--- |
| 1 | 1 | 20 |
| 2 | 1 | 20 |
| 1 | 2 | 30 |
| 2 | 2 | 30 |
| 3 | 2 | 40 |
| 1 | 3 | 40 |
| 3 | 3 | 60 |
| 1 | 4 | 60 |
| 3 | 4 | 70 |
| 1 | 7 | 90 |
| 1 | 8 | 90 |

**Output:**

| id | month | Salary |
| :--- | :--- | :--- |
| 1 | 7 | 90 |
| 1 | 4 | 130 |
| 1 | 3 | 90 |
| 1 | 2 | 50 |
| 1 | 1 | 20 |
| 2 | 1 | 20 |
| 3 | 3 | 100 |
| 3 | 2 | 40 |

**Giải thích:**

* **Nhân viên 1**: tháng mới nhất = 8 → loại tháng 8. Các tháng còn tính: 1, 2, 3, 4, 7.
  * Tháng 7: `90 + 0 (T6) + 0 (T5) = 90`
  * Tháng 4: `60 + 40 (T3) + 30 (T2) = 130`
  * Tháng 3: `40 + 30 (T2) + 20 (T1) = 90`
  * Tháng 2: `30 + 20 (T1) + 0 (T0) = 50`
  * Tháng 1: `20 + 0 + 0 = 20`
* **Nhân viên 2**: tháng mới nhất = 2 → loại tháng 2. Còn tháng 1: `20`.
* **Nhân viên 3**: tháng mới nhất = 4 → loại tháng 4. Còn tháng 2, 3.
  * Tháng 3: `60 + 40 (T2) + 0 (T1 nghỉ) = 100`
  * Tháng 2: `40 + 0 (T1) + 0 = 40`

---

## 2. Cách tiếp cận

Bài toán có **2 phép toán độc lập** có thể giải riêng rồi ghép lại:

* **A.** Tính tổng lương 3 tháng (cửa sổ trượt).
* **B.** Xác định tháng mới nhất của mỗi nhân viên để loại.

### Bước 1. Tính tổng lương 3 tháng bằng Window Function

Với mỗi dòng `(id, month)`, cần cộng lương của nó với hai tháng liền trước. Công cụ phù hợp là **window function `SUM()`** — cho phép mỗi dòng "nhìn sang" một nhóm dòng hàng xóm để tính toán mà **không làm mất dòng nào**.

Ba thành phần của cửa sổ:

* **`PARTITION BY id`**: chia bảng thành từng "phòng" theo nhân viên — mỗi nhân viên tính riêng, không ảnh hưởng nhau.
* **`ORDER BY month`**: trong mỗi phòng, sắp xếp các dòng theo tháng tăng dần (bắt buộc, để biết "trước" / "sau").
* **`RANGE BETWEEN 2 PRECEDING AND CURRENT ROW`**: với mỗi dòng, cửa sổ = mọi dòng có `month` nằm trong khoảng `[month_hiện_tại − 2, month_hiện_tại]`. Đây là phần quyết định — xem Bước 2.

Kết quả: mỗi dòng gốc được gắn thêm một cột `Salary` = tổng lương 3 tháng của dòng đó. Số dòng **không đổi**.

### Bước 2. ⚠️ Chọn `RANGE` hay `ROWS`? — Điểm mấu chốt

Đây là **cái bẫy lớn nhất** của bài toán. Nhân viên có thể nghỉ vài tháng → bảng **bị khuyết tháng**.

| Loại | Điều kiện lọc | Hành vi với tháng khuyết |
| :--- | :--- | :--- |
| `ROWS BETWEEN 2 PRECEDING` | Lấy **2 dòng vật lý** phía trước | ❌ Vơ đại tháng xa khi có tháng nghỉ |
| `RANGE BETWEEN 2 PRECEDING` | Lấy các dòng có **giá trị `month`** trong `[V-2, V]` | ✅ Tự động bỏ qua tháng khuyết |

**Ví dụ minh họa — nhân viên 1 có các tháng 1, 3, 4, 7, 8:**

Xét dòng `month = 7`:

* `RANGE`: điều kiện `month ∈ [5, 7]` → chỉ có tháng 7 → tổng = **90** ✅
* `ROWS`: lấy 2 dòng phía trước → tháng 3, 4, 7 → tổng = **190** ❌

**Kết luận:** Bắt buộc dùng `RANGE` cho bài này. Lý do: `RANGE` lọc theo **giá trị** của cột `ORDER BY`, còn `ROWS` lọc theo **vị trí dòng vật lý**. Với dữ liệu có thể khuyết như `month`, `RANGE` mới phản ánh đúng cửa sổ "3 tháng gần nhất".

### Bước 3. Xác định tháng mới nhất của mỗi nhân viên

Để loại tháng mới nhất, cần biết `MAX(month)` **của từng nhân viên**. Công cụ: window function `MAX(month) OVER (PARTITION BY id)`.

* **`MAX(month)`**: tìm giá trị tháng lớn nhất.
* **`PARTITION BY id`**: **tính riêng cho từng nhân viên** — đây là chỗ dễ sai nhất (xem Ghi chú #2).

Kết quả: mỗi dòng gốc được gắn thêm một cột `max_month` = tháng lớn nhất của nhân viên đó.

### Bước 4. Lọc và sắp xếp

Sau khi đã có `Salary` và `max_month` trong cùng một subquery/CTE, query ngoài chỉ cần:

* **`WHERE month != max_month`** → loại bỏ tháng mới nhất.
* **`ORDER BY id ASC, month DESC`** → sắp xếp theo yêu cầu đề bài.

### Tổng hợp — Sơ đồ tư duy

```text
┌─────────────────────────────────────────────┐
│  Subquery: tính đồng thời 2 window function │
│    - Salary    = SUM() OVER (RANGE ...)     │
│    - max_month = MAX() OVER (PARTITION id)  │
└─────────────────────┬───────────────────────┘
                      │
┌─────────────────────▼───────────────────────┐
│  Query ngoài: WHERE month != max_month      │
└─────────────────────┬───────────────────────┘
                      │
┌─────────────────────▼───────────────────────┐
│  ORDER BY id ASC, month DESC                │
└─────────────────────────────────────────────┘
```
---

## 3. Ghi chú

1. **`RANGE` vs `ROWS` — hiểu đúng bản chất**

   | | `ROWS` | `RANGE` |
   | :--- | :--- | :--- |
   | Đơn vị đếm | **Số dòng** vật lý | **Giá trị** cột `ORDER BY` |
   | Điều kiện lọc | vị trí dòng ∈ `[i-2, i]` | giá trị ∈ `[V-2, V]` |
   | Hành vi với dữ liệu khuyết | Sai (vơ dòng xa) | Đúng (tự thu hẹp cửa sổ) |

   **Quy tắc chọn:**

   * Dữ liệu **liên tục, không khuyết** (log giao dịch liên tiếp) → `ROWS` OK.
   * Dữ liệu **có thể khuyết** (tháng nghỉ, ngày không giao dịch) → **`RANGE` bắt buộc**.

2. **⚠️ Bug kinh điển: `MAX(month) OVER()` thiếu `PARTITION BY id`**

   Nếu bỏ quên `PARTITION BY id`, `max_month` sẽ là **tháng lớn nhất của TOÀN BỘ bảng** chứ không phải của từng nhân viên. Hậu quả:

   | id | max thật | `max_month` sai | Dòng bị loại nhầm |
   | :--- | :--- | :--- | :--- |
   | 1 | 8 | 8 | ✅ đúng |
   | 2 | 2 | 8 | ❌ tháng 2 **không** bị loại |
   | 3 | 4 | 8 | ❌ tháng 4 **không** bị loại |

   → Kết quả thừa dòng `(2, 2, ...)` và `(3, 4, ...)`. **Luôn nhớ `PARTITION BY id`.**

3. **Tại sao tháng khuyết tự động thành 0 mà không cần `COALESCE`?**

   Vì `RANGE` chỉ cộng các dòng **thực sự tồn tại** trong bảng. Tháng nghỉ không có dòng → không được cộng → tương đương 0. Đây là lý do `RANGE` "thần kỳ" xử lý được tháng khuyết mà không cần thêm logic.
