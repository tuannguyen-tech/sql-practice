# 571. Find Median Given Frequency of Numbers

* **Link:** [LeetCode 571 – Find Median Given Frequency of Numbers](https://leetcode.com/problems/find-median-given-frequency-of-numbers/)
* **Độ khó:** Hard
* **Chủ đề:** Window Function, CTE, Cumulative Frequency, Median

---

## 1. Đề bài

Bảng `Numbers` gồm các cột:

* `num`: Giá trị số.
* `frequency`: Số lần xuất hiện của giá trị `num`.

Yêu cầu: Tìm giá trị trung vị (Median) của toàn bộ dãy số.

Lưu ý: Bảng không lưu từng phần tử riêng lẻ mà sử dụng `frequency` để biểu diễn số lần xuất hiện của mỗi giá trị.

Ví dụ:

| num | frequency |
|---:|---:|
| 1 | 2 |
| 2 | 3 |
| 3 | 1 |

Dãy số thực tế tương ứng:

```text
[1, 1, 2, 2, 2, 3]
```

Tổng số phần tử là 6.

Median = (phần tử thứ 3 + phần tử thứ 4) / 2 = 2.0

---

## 2. Cách tiếp cận

### Bước 1. Tính tần suất tích lũy của từng giá trị

Để xác định vị trí của từng giá trị trong dãy số thực tế, trước tiên cần tính tổng tần suất từ giá trị nhỏ nhất đến giá trị hiện tại.

Sử dụng `SUM(frequency) OVER()` kết hợp với `ORDER BY num`:

```sql
SUM(frequency) OVER (
    ORDER BY num
    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
) AS cum_freq
```

Trong đó:

* `SUM(frequency)`: Tính tổng tần suất.
* `ORDER BY num`: Sắp xếp các giá trị theo thứ tự tăng dần.
* `UNBOUNDED PRECEDING`: Bắt đầu tính từ dòng đầu tiên.
* `CURRENT ROW`: Tính đến dòng hiện tại.

Kết quả:

| num | frequency | cum_freq |
|---:|---:|---:|
| 1 | 2 | 2 |
| 2 | 3 | 5 |
| 3 | 1 | 6 |

Từ `cum_freq`, có thể xác định khoảng vị trí mà mỗi giá trị `num` chiếm giữ:

```text
[num_start, num_end]
=
[cum_freq - frequency + 1, cum_freq]
```

Ví dụ:

* `num = 1` chiếm vị trí `[1, 2]`.
* `num = 2` chiếm vị trí `[3, 5]`.
* `num = 3` chiếm vị trí `[6, 6]`.

Như vậy, thay vì bung dữ liệu thành từng dòng riêng lẻ, ta có thể xác định vị trí của các phần tử thông qua khoảng tần suất.

### Bước 2. Xác định tổng số phần tử

Để tìm vị trí trung vị, cần biết tổng số phần tử trong toàn bộ dãy số.

Sử dụng `SUM(frequency) OVER()`:

```sql
SUM(frequency) OVER () AS total_freq
```

Trong đó:

* `SUM(frequency)`: Tính tổng số lần xuất hiện của tất cả giá trị.
* `OVER()`: Tính trên toàn bộ bảng, không chia thành từng nhóm.

### Bước 3. Xác định hai vị trí trung vị

Gọi `N` là tổng số phần tử (`total_freq`).

Có hai trường hợp:

* **Nếu N là số lẻ:** Vị trí trung vị nằm chính giữa, được xác định bởi `(N + 1) / 2`.
* **Nếu N là số chẵn:** Trung vị nằm ở hai vị trí liền kề `N / 2` và `N / 2 + 1`.

Sử dụng `CASE WHEN` để xác định hai vị trí này:

```sql
CASE
    WHEN total_freq % 2 = 0
        THEN total_freq / 2
    ELSE (total_freq + 1) / 2
END AS left_pos,

CASE
    WHEN total_freq % 2 = 0
        THEN total_freq / 2 + 1
    ELSE (total_freq + 1) / 2
END AS right_pos
```

### Bước 4. Xây dựng điều kiện lọc để tìm các giá trị trung vị

Sau khi xác định được hai vị trí trung vị, cần tìm những giá trị `num` tương ứng với các vị trí đó.

Mỗi giá trị `num` chiếm một khoảng vị trí:

```text
[cum_freq - frequency + 1, cum_freq]
```

**Vấn đề đặt ra:** Làm thế nào để xác định được tất cả các giá trị chứa vị trí trung vị bằng một điều kiện lọc duy nhất?

**Giải pháp:** Xây dựng một khoảng vị trí cần tìm `[left_pos, right_pos]`, sau đó tìm tất cả các khoảng tần suất có giao với khoảng này.

### Phân tích khoảng vị trí cần tìm

Xét hai trường hợp:

- **Với số lẻ (N = 5):**
  - Vị trí trung vị cần lấy là `3`.
  - Khi đó `left_pos = 3` và `right_pos = 3`.
  - Khoảng cần tìm là `[3, 3]`.

- **Với số chẵn (N = 8):**
  - Hai vị trí trung vị cần lấy là `4` và `5`.
  - Khi đó `left_pos = 4` và `right_pos = 5`.
  - Khoảng cần tìm là `[4, 5]`.

### Xây dựng điều kiện lọc chung

Để tìm tất cả các khoảng tần suất giao với đoạn `[left_pos, right_pos]`, cần thỏa mãn đồng thời hai điều kiện:

**Điều kiện 1:**

```sql
cum_freq >= left_pos
```

Vị trí kết thúc của khoảng tần suất hiện tại phải lớn hơn hoặc bằng vị trí trung vị bên trái.

**Điều kiện 2:**

```sql
cum_freq - frequency < right_pos
```

Vị trí ngay trước khoảng tần suất hiện tại phải nhỏ hơn vị trí trung vị bên phải.

Kết hợp hai điều kiện:

```sql
WHERE cum_freq >= left_pos
  AND cum_freq - frequency < right_pos
```

**Tại sao sử dụng AND thay vì OR?**

Vì cần tìm những khoảng tần suất có giao với đoạn `[left_pos, right_pos]`.

- Nếu hai vị trí trung vị nằm trong cùng một khoảng tần suất, chỉ có một dòng được chọn.
- Nếu hai vị trí trung vị nằm trong hai khoảng liên tiếp khác nhau, cả hai dòng đều được chọn.

**Ví dụ minh họa:**

Xét dãy số:

```text
[1, 1, 1, 1, 2, 2, 2, 3]
```

Tổng số phần tử `N = 8`.

Hai vị trí trung vị:

```text
left_pos  = 4
right_pos = 5
```

Các khoảng vị trí:

| num | frequency | Khoảng vị trí |
|---:|---:|---|
| 1 | 4 | [1, 4] |
| 2 | 3 | [5, 7] |
| 3 | 1 | [8, 8] |

Áp dụng điều kiện:

```sql
cum_freq >= 4
AND cum_freq - frequency < 5
```

Kết quả:

| num | Khoảng vị trí | Kết quả |
|---:|---|---|
| 1 | [1, 4] | Được chọn |
| 2 | [5, 7] | Được chọn |
| 3 | [8, 8] | Không được chọn |

Ta thấy:

* Vị trí thứ 4 thuộc giá trị `num = 1`.
* Vị trí thứ 5 thuộc giá trị `num = 2`.

Hai vị trí trung vị nằm ở hai khoảng tần suất khác nhau nhưng đều được chọn bởi cùng một điều kiện lọc.

Do đó:

```text
Median = (1 + 2) / 2 = 1.5
```

**Kết luận:** Khoảng `[left_pos, right_pos]` giúp xử lý đồng thời trường hợp tổng số phần tử chẵn và lẻ. Điều kiện lọc sẽ tìm tất cả các khoảng tần suất giao với khoảng này.

Sau đó, sử dụng `AVG(num)` để tính giá trị trung vị.

---

## 3. Ghi chú

1. **Phân biệt SUM() OVER() và SUM() OVER(ORDER BY)**

   * `SUM(frequency) OVER()`: Tính tổng tần suất của toàn bộ bảng.
   * `SUM(frequency) OVER(ORDER BY num ...)`: Tính tần suất tích lũy theo thứ tự của `num`.

2. **Bản chất của Cumulative Frequency**

   `cum_freq` biểu diễn vị trí kết thúc của khoảng tần suất hiện tại.

   `cum_freq - frequency` biểu diễn vị trí ngay trước khi khoảng hiện tại bắt đầu.

   Vì vậy, khoảng vị trí của mỗi giá trị được xác định bởi:

   ```text
   [cum_freq - frequency + 1, cum_freq]
   ```

3. **Tại sao sử dụng AND thay vì OR?**

   Hai điều kiện phải đồng thời đúng để khoảng tần suất hiện tại giao với đoạn vị trí cần tìm `[left_pos, right_pos]`.

   Sử dụng `OR` sẽ khiến những khoảng chỉ thỏa mãn một phía cũng được chọn, dẫn đến kết quả sai.

4. **Hai vị trí trung vị không nhất thiết nằm trong cùng một khoảng**

   Với tổng số phần tử chẵn, hai vị trí trung vị có thể:

   * Nằm trong cùng một khoảng tần suất.
   * Nằm trong hai khoảng tần suất liên tiếp khác nhau.
---
