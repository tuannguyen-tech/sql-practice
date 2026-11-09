# Codeforces 2254B - Evanescent

**Topic:** Strings, Greedy, Observation (Quan sát)  
**Platform:** Codeforces  
**Problem:** Evanescent

---

## 1. Phân tích bài toán (Problem Analysis)

Cho một chuỗi `s` có độ dài `n`.

Ta được phép xóa đúng một ký tự ở vị trí nằm giữa chuỗi (không được xóa ký tự đầu tiên hoặc cuối cùng).

Sau khi xóa, chuỗi sẽ được nén bằng cách gộp các ký tự liên tiếp giống nhau thành một ký tự duy nhất.

Ví dụ:

```text
Original:   AAABCCDD
Compressed: ABCD
```

**Yêu cầu:** Tìm độ dài chuỗi sau khi thực hiện thao tác xóa và nén sao cho kết quả nhỏ nhất.

Thay vì thử xóa từng ký tự rồi nén lại toàn bộ chuỗi, ta cần tìm cách xác định mức độ thay đổi khi xóa một ký tự.

---

## 2. Tính độ dài chuỗi nén ban đầu (Original Compressed Length)

Trước tiên, tính độ dài chuỗi sau khi nén nhưng chưa thực hiện thao tác xóa.

Đặt:

$$L = compressedLength$$

**### 2.1. Ý tưởng**

Mỗi khi hai ký tự liên tiếp khác nhau, ta bắt đầu một nhóm ký tự mới.

Do đó:
- Khởi tạo `compressedLength = 1`.
- Duyệt chuỗi từ vị trí `1` đến `n-1`.
- Nếu `s[i] != s[i-1]`, tăng `compressedLength` lên 1.

**### 2.2. Ví dụ**

```text
s = AAABCCDD

Index:       0 1 2 3 4 5 6 7
Character:   A A A B C C D D
```

Các nhóm ký tự:

```text
AAA | B | CC | DD
```

Chuỗi sau khi nén:

```text
ABCD
```

Vậy:

$$compressedLength = 4$$

**Ghi nhớ:** Số nhóm ký tự liên tiếp chính là độ dài chuỗi sau khi nén.

---

## 3. Phân tích ảnh hưởng khi xóa một ký tự (Local Change)

Đây là phần quan trọng nhất của bài toán.

Thay vì mô phỏng việc xóa từng ký tự, ta chỉ cần quan sát ba ký tự liên tiếp:

$$s[i-1],\ s[i],\ s[i+1]$$

Khi xóa `s[i]`, chỉ có hai mối liên kết giữa ký tự bên trái, ký tự hiện tại và ký tự bên phải bị thay đổi.

Ta chia thành ba trường hợp.

**### 3.1. Trường hợp giảm 2 đơn vị**

Điều kiện:

```cpp
s[i] != s[i - 1] &&
s[i] != s[i + 1] &&
s[i - 1] == s[i + 1]
```

Ví dụ:

```text
Before: A B A
Delete:   B
After:  A A
```

Phân tích:

- Ban đầu có 3 nhóm: `A | B | A`.
- Xóa `B`, hai nhóm `A` được gộp lại thành một nhóm.
- Mất một nhóm `B` và giảm thêm một nhóm do gộp hai nhóm `A`.

Do đó:

$$\Delta = 2$$

Đây là mức giảm lớn nhất có thể đạt được.

**### 3.2. Trường hợp giảm 1 đơn vị**

Điều kiện:

```cpp
s[i] != s[i - 1] &&
s[i] != s[i + 1] &&
s[i - 1] != s[i + 1]
```

Ví dụ:

```text
Before: A B C
Delete:   B
After:  A C
```

Phân tích:

- Ban đầu có 3 nhóm: `A | B | C`.
- Xóa `B`, nhóm `B` biến mất.
- Hai nhóm `A` và `C` vẫn khác nhau nên không được gộp.

Do đó:

$$\Delta = 1$$

**### 3.3. Trường hợp giảm 0 đơn vị**

Nếu ký tự hiện tại giống ký tự bên trái hoặc bên phải thì việc xóa nó không làm mất nhóm ký tự tương ứng.

Ví dụ:

```text
Before: A A B
Delete:   A
After:  A B
```

Phân tích:

- Ban đầu có 2 nhóm: `AA | B`.
- Sau khi xóa một ký tự `A`, nhóm `A` vẫn còn.
- Số nhóm không thay đổi.

Do đó:

$$\Delta = 0$$

**Ghi nhớ:** Muốn giảm độ dài nén, ký tự bị xóa phải là một nhóm riêng lẻ, tức là khác cả hai ký tự bên cạnh.

---

## 4. Chiến lược Greedy (Tìm mức giảm lớn nhất)

Sau khi phân tích ba trường hợp, ta nhận thấy mức giảm chỉ có thể là:

$$\Delta \in \{0,1,2\}$$

Vì mục tiêu là tìm độ dài nhỏ nhất, ta cần tìm vị trí xóa có mức giảm lớn nhất.

Đặt:

$$maxReduction = \max(\Delta)$$

**### 4.1. Duyệt tìm vị trí phù hợp**

Duyệt các vị trí từ `1` đến `n-2`.

Tại mỗi vị trí `i`, xét:

**Trường hợp 1:** Nếu hai ký tự bên cạnh giống nhau và ký tự giữa khác chúng:

```cpp
if (s[i] != s[i + 1] && s[i - 1] == s[i + 1])
```

Ta có thể giảm 2 đơn vị.

Cập nhật:

```cpp
maxReduction = 2;
break;
```

Vì 2 là mức giảm tối đa nên không cần tìm kiếm tiếp.

**Trường hợp 2:** Nếu ký tự giữa khác cả hai ký tự bên cạnh:

```cpp
if (s[i] != s[i + 1] && s[i - 1] != s[i])
```

Ta có thể giảm 1 đơn vị.

Cập nhật:

```cpp
maxReduction = 1;
```

Không dừng vòng lặp vì vẫn có thể tìm được vị trí giảm 2.

**Trường hợp 3:** Nếu không thỏa mãn hai điều kiện trên, mức giảm bằng 0.

Giữ nguyên `maxReduction`.

**### 4.2. Tính kết quả cuối cùng**

Ban đầu có:

$$L = compressedLength$$

Sau khi tìm được mức giảm lớn nhất:

$$answer = L - maxReduction$$

Ví dụ:

```text
compressedLength = 5
maxReduction = 2

answer = 5 - 2 = 3
```

**Ghi nhớ:** Greedy ở đây không phải thử tất cả phương án rồi mô phỏng lại, mà là tìm mức cải thiện lớn nhất có thể đạt được.

---

## 5. Kinh nghiệm triển khai C++

**### 5.1. Đặt tên biến theo ý nghĩa**

| Variable | Meaning |
|---|---|
| `n` | Độ dài chuỗi |
| `s` | Chuỗi đầu vào |
| `compressedLength` | Độ dài chuỗi sau khi nén ban đầu |
| `maxReduction` | Mức giảm lớn nhất khi xóa một ký tự |
| `testCases` | Số lượng bộ test |

**### 5.2. Sử dụng `break` để tối ưu**

```cpp
if (s[i] != s[i + 1] && s[i - 1] == s[i + 1]) {
    maxReduction = 2;
    break;
}
```

Vì mức giảm tối đa chỉ là 2, khi tìm được trường hợp này thì không cần tiếp tục duyệt.

**### 5.3. Phân biệt chỉ số vòng lặp**

```cpp
for (int i = 1; i <= n - 2; i++)
```

Tại sao bắt đầu từ `1` và kết thúc ở `n-2`?

- Không được xóa ký tự đầu tiên.
- Không được xóa ký tự cuối cùng.
- Cần truy cập `s[i-1]` và `s[i+1]`, vì vậy phải đảm bảo hai vị trí này hợp lệ.

---

## 6. Độ phức tạp thuật toán (Complexity Analysis)

| Complexity | Value | Explanation |
|---|---|---|
| Time | O(n) | Duyệt chuỗi hai lần |
| Space | O(1) | Chỉ sử dụng các biến phụ, không tạo chuỗi mới |

Với mỗi test case, thuật toán có độ phức tạp:

$$T(n) = O(n)$$

---

## 7. Tổng kết tư duy giải quyết bài toán

Khi gặp bài toán yêu cầu xóa một phần tử trong chuỗi để tối ưu một đại lượng, hãy thử áp dụng quy trình sau:

**### Bước 1. Tính trạng thái ban đầu**

Xác định kết quả của chuỗi trước khi thực hiện thao tác.

**### Bước 2. Xác định phạm vi ảnh hưởng**

Tìm hiểu việc xóa một ký tự ảnh hưởng đến những phần tử nào.

Trong bài này, chỉ cần quan sát ba ký tự liên tiếp:

$$s[i-1],\ s[i],\ s[i+1]$$

**### Bước 3. Phân loại mức độ thay đổi**

Xác định các trường hợp có thể xảy ra:

- Giảm 0.
- Giảm 1.
- Giảm 2.

**### Bước 4. Áp dụng Greedy**

Tìm mức giảm lớn nhất thay vì thử và mô phỏng mọi phương án.

**### Bước 5. Tính kết quả**

Lấy trạng thái ban đầu trừ đi mức cải thiện lớn nhất.

---

## 8. Những kiến thức cần ghi nhớ

- [ ] Biết cách đếm số nhóm ký tự liên tiếp trong chuỗi.
- [ ] Hiểu cách nén chuỗi bằng cách gom các ký tự giống nhau.
- [ ] Hiểu tại sao chỉ cần xét ba ký tự liên tiếp khi xóa một ký tự.
- [ ] Phân biệt được ba trường hợp giảm 0, 1 và 2.
- [ ] Hiểu cách sử dụng `maxReduction` để lưu mức giảm lớn nhất.
- [ ] Hiểu tại sao có thể sử dụng `break` khi tìm được mức giảm 2.
- [ ] Biết áp dụng tư duy Local Change / Delta Approach.
- [ ] Biết kết hợp Greedy với phân tích ảnh hưởng cục bộ.
- [ ] Tự triển khai lại thuật toán mà không cần xem lời giải.

---

## 9. Bài học quan trọng nhất

**Local Change (Thay đổi cục bộ):**

Không phải lúc nào cũng cần mô phỏng lại toàn bộ trạng thái sau mỗi thao tác.

Hãy thử:
1. Tính kết quả ban đầu.
2. Phân tích phần bị ảnh hưởng bởi thao tác.
3. Tính mức thay đổi thay vì tính lại toàn bộ kết quả.
4. Chọn thao tác mang lại kết quả tốt nhất.

Đây là một tư duy hữu ích khi giải các bài toán String, Array và Greedy trong Competitive Programming.