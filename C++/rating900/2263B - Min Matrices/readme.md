# Codeforces 2263B - Min Matrices

**Topic:** Constructive Algorithms (Thuật toán dựng)  
**Platform:** Codeforces  
**Problem:** Min Matrices

---

## 1. Phân tích điều kiện biên (Boundaries & Edge Cases)

Trước khi xây dựng ma trận, cần xác định những trường hợp không thể tạo ra kết quả hợp lệ.

### 1.1. Điều kiện giới hạn dưới: `k < n`

- Ma trận có `n` hàng.
- Mỗi hàng có một giá trị nhỏ nhất (minimum).
- Vì các giá trị minimum của các hàng phải phân biệt, ta cần ít nhất `n` giá trị khác nhau.

Do đó:

$$k \ge n$$

Nếu `k < n`, không tồn tại đáp án hợp lệ.

### 1.2. Điều kiện giới hạn trên: `k >= 2n`

- Ma trận có `n` hàng và `n` cột.
- Tổng số giá trị minimum của tất cả hàng và cột tối đa là `2n`.
- Tuy nhiên, luôn có ít nhất một giá trị minimum chung giữa một hàng và một cột.

Vì vậy, số lượng giá trị phân biệt tối đa là:

$$|f(A)| \le 2n-1$$

### 1.3. Kết luận

Nếu:

$$k < n \quad \text{hoặc} \quad k \ge 2n$$

In ra `-1`.

---

## 2. Xây dựng cấu trúc cơ sở (Baseline Construction)

Thay vì cố gắng xây dựng ngay ma trận có đúng `k` giá trị minimum, ta bắt đầu từ trường hợp đơn giản nhất: tạo ra đúng `n` giá trị phân biệt.

### 2.1. Ý tưởng xây dựng

Đặt các số từ `1` đến `n` trên đường chéo chính:

$$A[i][i] = i$$

Các ô còn lại được điền bằng những số lớn hơn `n`.

Ví dụ với `n = 3`:

```text
1  4  5
6  2  7
8  9  3
```

### 2.2. Tại sao cách này hoạt động?

- Hàng 1 có minimum là `1`.
- Hàng 2 có minimum là `2`.
- Hàng 3 có minimum là `3`.
- Cột 1 có minimum là `1`.
- Cột 2 có minimum là `2`.
- Cột 3 có minimum là `3`.

Tập hợp các giá trị minimum:

$$f(A) = \{1, 2, 3\}$$

Có đúng `n = 3` giá trị phân biệt.

**Ghi nhớ:** Đường chéo chính giúp mỗi hàng và mỗi cột có một giá trị minimum riêng, trong khi các phần tử còn lại đủ lớn để không ảnh hưởng đến minimum.

---

## 3. Kỹ thuật tăng dần (Incremental Construction)

Sau khi có cấu trúc cơ sở với `n` giá trị minimum, ta cần tăng số lượng này lên đúng `k`.

Đặt:

$$shift = k - n$$

Đây là số lượng giá trị minimum mới cần tạo thêm.

### 3.1. Thao tác biến đổi

Lần lượt hoán đổi các phần tử trên đường chéo chính từ hàng thứ `2` đến hàng thứ `shift + 1` về cột đầu tiên.

Cụ thể:

```cpp
swap(A[r][r], A[r][1]);
```

Với:

$$r = 2, 3, \ldots, shift + 1$$

### 3.2. Tại sao thao tác này tạo thêm một minimum mới?

Xét thao tác hoán đổi:

```cpp
swap(A[r][r], A[r][1]);
```

Ta phân tích ảnh hưởng đến các hàng và cột:

**1. Minimum của hàng `r` không thay đổi**

Giá trị `r` vẫn nằm trong hàng `r`, chỉ chuyển từ cột `r` sang cột `1`.

Do đó:

$$min(row_r) = r$$

**2. Minimum của cột 1 không thay đổi**

Cột 1 đã chứa giá trị `1`, là giá trị nhỏ nhất.

Việc đưa thêm một giá trị lớn hơn vào cột này không làm thay đổi minimum.

**3. Minimum của cột `r` thay đổi**

Giá trị `r` bị chuyển khỏi vị trí `A[r][r]`.

Các phần tử còn lại trong cột `r` đều lớn hơn `n`, vì vậy minimum mới của cột này là một giá trị lớn hơn `n`.

Như vậy, mỗi lần thực hiện một phép hoán đổi, ta tạo ra đúng một giá trị minimum mới.

### 3.3. Kết quả

Ban đầu có:

$$n$$

giá trị minimum phân biệt.

Sau `shift` lần hoán đổi:

$$|f(A)| = n + shift$$

Thay `shift = k - n`:

$$|f(A)| = n + (k-n) = k$$

Đáp ứng yêu cầu bài toán.

**Ghi nhớ:** Mỗi phép biến đổi chỉ làm thay đổi minimum của một cột, không phá vỡ các minimum đã có.

---

## 4. Kinh nghiệm triển khai C++

### 4.1. Khởi tạo vector 2 chiều

Có thể sử dụng:

```cpp
vector<vector<long long>> ans(
    n + 1,
    vector<long long>(n + 1)
);
```

**Tại sao sử dụng `n + 1`?**

- Giúp sử dụng chỉ số từ `1` đến `n` (1-indexed).
- Chỉ số trong code trùng với cách đánh số hàng và cột trong đề bài.
- Hạn chế lỗi `off-by-one` khi truy cập phần tử.

### 4.2. Sử dụng hàm `swap()`

Hàm `swap()` dùng để hoán đổi giá trị của hai biến.

```cpp
swap(ans[r][r], ans[r][1]);
```

Có thể sử dụng hàm này thông qua thư viện:

```cpp
#include <bits/stdc++.h>
using namespace std;
```

### 4.3. Tối ưu Input/Output

Trong các bài lập trình thi đấu, nên sử dụng:

```cpp
ios_base::sync_with_stdio(false);
cin.tie(nullptr);
```

Giúp tăng tốc độ đọc và ghi dữ liệu khi xử lý lượng input/output lớn.

---

## 5. Tổng kết tư duy giải Constructive Algorithms

Khi gặp bài toán yêu cầu xây dựng ma trận, dãy số hoặc cấu trúc thỏa mãn một số điều kiện, hãy áp dụng quy trình tư duy sau:

### Bước 1. Xác định điều kiện bất khả thi

Tìm giới hạn nhỏ nhất và lớn nhất mà kết quả có thể đạt được.

### Bước 2. Xây dựng cấu trúc cơ sở

Bắt đầu từ một trường hợp đơn giản nhất, dễ kiểm soát và dễ chứng minh tính đúng đắn.

### Bước 3. Tìm thao tác biến đổi cục bộ

Tìm một thao tác có thể làm thay đổi kết quả theo từng bước nhỏ.

### Bước 4. Chứng minh tính độc lập của thao tác

Đảm bảo mỗi lần biến đổi chỉ ảnh hưởng đến thành phần mong muốn, không phá vỡ những điều kiện đã thỏa mãn trước đó.

### Bước 5. Kiểm tra kết quả

Chứng minh rằng sau tất cả các thao tác, cấu trúc thu được thỏa mãn chính xác yêu cầu đề bài.

---

## 6. Những kiến thức cần ghi nhớ

- [ ] Phân tích điều kiện biên trước khi xây dựng đáp án.
- [ ] Tìm cấu trúc cơ sở đơn giản nhất.
- [ ] Sử dụng đường chéo chính để kiểm soát minimum của hàng và cột.
- [ ] Hiểu cách sử dụng `shift = k - n`.
- [ ] Biết sử dụng `swap()` để thay đổi vị trí phần tử.
- [ ] Phân tích ảnh hưởng của một phép biến đổi đến toàn bộ cấu trúc.
- [ ] Chứng minh mỗi thao tác tạo ra đúng một giá trị mới.
- [ ] Sử dụng `vector<vector<long long>>` để khởi tạo ma trận 2 chiều.
- [ ] Phân biệt chỉ số 0-indexed và 1-indexed.

---

## 7. Bài học quan trọng nhất

Trong Constructive Algorithms, không nhất thiết phải tìm ngay đáp án cuối cùng.

Hãy xây dựng một cấu trúc cơ sở đúng trước, sau đó tìm cách biến đổi cấu trúc đó từng bước để đạt được yêu cầu của đề bài.

Đây là một tư duy quan trọng cần rèn luyện khi giải các bài toán Constructive Algorithms trên Codeforces.