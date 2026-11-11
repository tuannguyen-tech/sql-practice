# Codeforces 2246B – ezraft and Array

**Topic:** Constructive Algorithms (Thuật toán dựng), Number Theory (Lý thuyết số)  
**Platform:** Codeforces  
**Problem:** ezraft and Array  
**Difficulty:** 900

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán yêu cầu xây dựng một mảng `a` gồm `n` số nguyên dương khác nhau sao cho thỏa mãn điều kiện:

**Input:** Một số nguyên `n` cho mỗi test case.

**Yêu cầu:**

- Mảng `a = [a₁, a₂, ..., aₙ]` gồm `n` số nguyên dương.
- Tất cả phần tử trong mảng phải khác nhau.
- Tổng của toàn bộ mảng phải chia hết cho từng phần tử.

Công thức:

$$
S = a_1+a_2+\ldots+a_n
$$

Điều kiện:

$$
S \bmod a_i = 0
$$

Với mọi `i` từ `1` đến `n`.

**Giới hạn:**

- `1 ≤ n ≤ 50`
- `1 ≤ aᵢ ≤ 10¹⁷`

**Mục tiêu:** Xây dựng một mảng thỏa mãn tất cả điều kiện hoặc in `-1` nếu không tồn tại lời giải.

---

## 2. Phân tích tư duy và điều kiện bất khả thi (Key Insights)

Trước khi tìm cách xây dựng mảng, cần xác định những trường hợp nào không thể có lời giải.

### 2.1. Trường hợp 1: n = 1

**Kết luận: Có nghiệm.**

Khi `n = 1`, mảng chỉ có một phần tử.

Ta chọn:

```text
a = [1]
```

Tổng của mảng:

$$
S=1
$$

Kiểm tra điều kiện:

$$
1 \bmod 1 = 0
$$

Tổng chia hết cho phần tử duy nhất trong mảng.

Vậy `n = 1` luôn có nghiệm.

### 2.2. Trường hợp 2: n = 2

**Kết luận: Không có nghiệm (-1).**

Giả sử mảng có hai phần tử nguyên dương khác nhau là `a` và `b`.

Tổng của mảng:

$$
S=a+b
$$

Theo yêu cầu đề bài, tổng phải chia hết cho từng phần tử.

**Điều kiện 1: Tổng chia hết cho a**

$$
(a+b)\bmod a=0
$$

Vì `a` chia hết cho chính nó:

$$
a\bmod a=0
$$

Nên:

$$
b\bmod a=0
$$

Điều này có nghĩa là `b` phải chia hết cho `a`.

**Điều kiện 2: Tổng chia hết cho b**

Tương tự:

$$
(a+b)\bmod b=0
$$

Suy ra:

$$
a\bmod b=0
$$

Điều này có nghĩa là `a` phải chia hết cho `b`.

**Kết hợp hai điều kiện:**

- `b` chia hết cho `a`.
- `a` chia hết cho `b`.

Với hai số nguyên dương, điều này chỉ xảy ra khi:

$$
a=b
$$

Tuy nhiên, đề bài yêu cầu hai phần tử phải khác nhau.

Đây là mâu thuẫn với yêu cầu đề bài.

**Kết luận:**

$$
n=2 \Rightarrow -1
$$

### 2.3. Trường hợp 3: n ≥ 3

**Kết luận: Luôn tồn tại nghiệm.**

Ta cần tìm cách xây dựng một mảng có ít nhất 3 phần tử sao cho tổng chia hết cho tất cả phần tử.

Thử một mảng đơn giản:

```text
a = [1, 2, 3]
```

Tổng:

$$
S=1+2+3=6
$$

Kiểm tra:

- `6` chia hết cho `1`.
- `6` chia hết cho `2`.
- `6` chia hết cho `3`.

Như vậy, ta đã tìm được một mảng hợp lệ ban đầu.

**Câu hỏi quan trọng:** Làm thế nào để thêm phần tử mới mà không phá vỡ điều kiện ban đầu?

Đây chính là chìa khóa để giải quyết bài toán.

---

## 3. Chiến lược xây dựng mảng (Constructive Strategy)

Khi đã có mảng ban đầu `[1, 2, 3]`, ta tìm cách mở rộng mảng cho đến khi đủ `n` phần tử.

### 3.1. Ý tưởng: Thêm chính tổng hiện tại

Giả sử mảng hiện tại có tổng là `S`.

Ta biết:

$$
a_i \mid S
$$

Với tất cả phần tử hiện tại.

Thay vì chọn một số bất kỳ, ta thử thêm chính tổng hiện tại `S` vào mảng.

Khi đó:

$$
a_{new}=S
$$

Tổng mới:

$$
S_{new}=S+S=2S
$$

Như vậy, tổng mới gấp đôi tổng cũ.

**Ví dụ:**

Ban đầu:

```text
a = [1, 2, 3]
S = 6
```

Lần 1: Thêm `6`.

```text
a = [1, 2, 3, 6]
S = 12
```

Lần 2: Thêm `12`.

```text
a = [1, 2, 3, 6, 12]
S = 24
```

Lần 3: Thêm `24`.

```text
a = [1, 2, 3, 6, 12, 24]
S = 48
```

Ta nhận thấy quy luật:

$$
S_{new}=2S
$$

Mỗi lần thêm phần tử mới, tổng hiện tại tăng gấp đôi.

**Công thức mảng được xây dựng:**

$$
a=[1,2,3,6,12,24,\ldots]
$$

Hay với các phần tử từ vị trí thứ 4 trở đi:

$$
a_i=3\times 2^{i-3}
$$

### 3.2. Chứng minh tính đúng đắn (Correctness Proof)

Cần chứng minh mảng được xây dựng thỏa mãn ba điều kiện:

- Tất cả phần tử đều là số nguyên dương.
- Tất cả phần tử đều khác nhau.
- Tổng của mảng chia hết cho từng phần tử.

**Điều kiện 1: Tất cả phần tử đều là số nguyên dương.**

Ba phần tử ban đầu là:

```text
1, 2, 3
```

Các phần tử tiếp theo được tạo bằng cách nhân phần tử trước đó với `2`.

Vì tất cả phần tử ban đầu đều dương và phép nhân với `2` không làm thay đổi tính dương nên tất cả phần tử đều là số nguyên dương.

**Điều kiện 2: Tất cả phần tử đều khác nhau.**

Ba phần tử ban đầu `1, 2, 3` khác nhau.

Các phần tử tiếp theo lần lượt là:

```text
6, 12, 24, 48, ...
```

Mỗi phần tử mới gấp đôi phần tử trước đó.

Do đó, mỗi phần tử mới luôn lớn hơn phần tử đứng trước.

Vậy tất cả phần tử trong mảng đều khác nhau.

**Điều kiện 3: Tổng chia hết cho tất cả phần tử.**

Đây là điều kiện quan trọng nhất.

Ta chứng minh bằng cách xét quá trình xây dựng mảng.

*Bước khởi tạo:*

Mảng ban đầu:

```text
[1, 2, 3]
```

Tổng:

$$
S=1+2+3=6
$$

Ta có:

$$
6\bmod 1=0
$$

$$
6\bmod 2=0
$$

$$
6\bmod 3=0
$$

Vậy mảng ban đầu hợp lệ.

*Bước mở rộng:*

Giả sử mảng hiện tại có tổng là `S` và tất cả phần tử đều chia hết `S`.

Ta thêm phần tử mới:

$$
a_{new}=S
$$

Tổng mới:

$$
S_{new}=S+a_{new}=2S
$$

Xét hai trường hợp:

**Trường hợp A: Các phần tử cũ**

Theo giả thiết:

$$
a_i\mid S
$$

Suy ra:

$$
a_i\mid 2S
$$

Hay:

$$
a_i\mid S_{new}
$$

Như vậy, tất cả phần tử cũ vẫn chia hết tổng mới.

**Trường hợp B: Phần tử mới**

Phần tử mới chính là `S`.

Ta có:

$$
S_{new}=2S
$$

Nên:

$$
S_{new}\bmod a_{new}=0
$$

Phần tử mới cũng chia hết tổng mới.

**Kết luận:**

Sau mỗi lần thêm phần tử, tổng mới vẫn chia hết cho tất cả phần tử trong mảng.

Vì mảng ban đầu hợp lệ và mỗi bước mở rộng đều bảo toàn điều kiện nên mảng được xây dựng luôn hợp lệ.

Đây là kỹ thuật **Invariant (Bất biến)** trong thuật toán.

### 3.3. Kiểm tra giới hạn giá trị (Constraint Verification)

Đề bài yêu cầu:

$$
1\leq a_i\leq 10^{17}
$$

Với `n ≤ 50`, phần tử lớn nhất là phần tử thứ 50:

$$
a_{50}=3\times 2^{47}
$$

$$
a_{50}=422212465065984
$$

Ta có:

$$
422212465065984 < 10^{17}
$$

Vì vậy, tất cả phần tử đều nằm trong giới hạn đề bài.

**Lưu ý khi cài đặt C++:**

Phải sử dụng `long long` thay vì `int` vì giá trị các phần tử có thể vượt quá giới hạn của `int`.

---

## 4. Bài học rút ra (Key Takeaways)

Bài toán mang lại 4 bài học quan trọng khi giải các bài Constructive Algorithms.

### 1. Tìm điều kiện bất khả thi (Impossibility Boundary)

Trước khi tìm cách xây dựng đáp án, hãy kiểm tra những trường hợp không thể tồn tại nghiệm.

Ở bài này:

- `n = 1`: Có nghiệm.
- `n = 2`: Không có nghiệm.
- `n ≥ 3`: Luôn có nghiệm.

Việc phân tích các trường hợp nhỏ giúp xác định chính xác phạm vi có thể xây dựng lời giải.

### 2. Tư duy mở rộng lời giải (Incremental Construction)

Khi đã tìm được một mảng hợp lệ ban đầu, đừng vội tìm một công thức phức tạp để xây dựng toàn bộ mảng.

Hãy đặt câu hỏi:

**Làm thế nào để thêm một phần tử mới mà vẫn giữ nguyên tính chất hợp lệ của mảng?**

Ở bài này, ta thêm chính tổng hiện tại vào mảng.

### 3. Sử dụng bất biến (Invariant)

Bất biến là một tính chất luôn đúng trong suốt quá trình thực hiện thuật toán.

Ở bài này, bất biến là:

$$
a_i\mid S
$$

Tức là tổng hiện tại luôn chia hết cho tất cả phần tử đã được xây dựng.

Khi thêm `S` vào mảng:

$$
S_{new}=2S
$$

Bất biến vẫn được duy trì.

### 4. Kiểm tra kiểu dữ liệu (Data Type Verification)

Không phải lúc nào `int` cũng đủ để lưu trữ kết quả.

Ở bài này, phần tử lớn nhất có thể đạt đến:

$$
3\times 2^{47}
$$

Vì vậy, cần sử dụng `long long` để tránh lỗi `signed integer overflow`.

---

## 5. Tổng kết tư duy giải bài

Có thể ghi nhớ toàn bộ hướng giải bằng quy trình sau:

1. Nếu `n = 1` → In `1`.
2. Nếu `n = 2` → In `-1`.
3. Nếu `n ≥ 3`:
   - Khởi tạo mảng `[1, 2, 3]`.
   - Đặt `sum = 6`.
   - Trong khi số phần tử chưa đủ `n`:
     - Thêm `sum` vào mảng.
     - Cập nhật `sum = sum * 2`.
4. In các phần tử trong mảng.

**Ý tưởng cốt lõi:**

Bắt đầu bằng một mảng nhỏ hợp lệ `[1, 2, 3]`, sau đó mỗi lần thêm chính tổng hiện tại vào mảng. Vì tổng mới luôn gấp đôi tổng cũ nên tất cả phần tử cũ và phần tử mới đều tiếp tục chia hết tổng mới.

---

## 6. Độ phức tạp (Complexity Analysis)

Với mỗi test case:

**Time Complexity:**

$$
O(n)
$$

Vì cần thực hiện tối đa `n - 3` lần thêm phần tử.

**Space Complexity:**

$$
O(n)
$$

Vì cần lưu trữ mảng gồm `n` phần tử.

