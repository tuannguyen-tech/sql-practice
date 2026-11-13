# Codeforces 2210B – Simply Sitting on Chairs

**Topic:** Greedy, Permutation, Array

**Platform:** Codeforces

**Problem:** Simply Sitting on Chairs

**Difficulty:** 900

**Contest:** Codeforces Round 1089 (Div. 2)

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán cho một hàng gồm `n` chiếc ghế, được đánh số từ `1` đến `n`. Ban đầu, tất cả các ghế đều chưa được đánh dấu.

Ta được cung cấp một hoán vị `p` có độ dài `n`.

Một hoán vị là một mảng gồm `n` số nguyên khác nhau từ `1` đến `n`.

Ta thực hiện trò chơi bằng cách lần lượt đi qua từng chiếc ghế, bắt đầu từ ghế thứ nhất.

Tại ghế thứ `i`, có hai trường hợp:

**Trường hợp 1: Ghế đã được đánh dấu.**

- Trò chơi kết thúc ngay lập tức.
- Không được ngồi lên chiếc ghế đó.

**Trường hợp 2: Ghế chưa được đánh dấu.**

Ta có hai lựa chọn:

- Ngồi lên ghế thứ `i`.
- Bỏ qua ghế thứ `i` và chuyển sang ghế tiếp theo.

Nếu chọn ngồi lên ghế thứ `i`:

- Sau khi đứng dậy, ghế thứ `p[i]` sẽ được đánh dấu.
- Sau đó tiếp tục di chuyển đến ghế tiếp theo.

Trò chơi cũng kết thúc nếu ta đã đi qua tất cả `n` chiếc ghế.

**Yêu cầu bài toán:**

Tìm số lượng ghế lớn nhất mà ta có thể ngồi lên bằng cách lựa chọn chiến lược phù hợp.

**Input:**

- Dòng đầu tiên chứa số lượng test case `t`.
- Mỗi test case gồm:
  - Số nguyên `n`: số lượng ghế.
  - Hoán vị `p` gồm `n` phần tử.

**Output:**

Với mỗi test case, in ra một số nguyên là số lượng ghế tối đa có thể ngồi lên.

**Constraints:**

- `1 ≤ t ≤ 10^4`
- `1 ≤ n ≤ 2 × 10^5`
- `p` là một hoán vị của `[1, n]`.
- Tổng `n` của tất cả test case không vượt quá `2 × 10^5`.

---

## 2. Phân tích tư duy và nhận xét quan trọng

### 2.1. Hiểu bản chất của thao tác đánh dấu

Điều quan trọng nhất của bài toán là hiểu rằng:

Khi ngồi lên ghế thứ `i`, ta sẽ đánh dấu ghế thứ `p[i]`.

Điều này tạo ra hai trường hợp hoàn toàn khác nhau.

**Trường hợp 1: `p[i] ≤ i`**

Ghế được đánh dấu nằm ở vị trí hiện tại hoặc phía trước vị trí hiện tại.

Ví dụ:

- Đang ở ghế 3.
- `p[3] = 2`.
- Khi ngồi lên ghế 3, ghế 2 được đánh dấu.

Tuy nhiên, ta đã đi qua ghế 2 rồi.

Vì vậy, việc đánh dấu này không ảnh hưởng đến những chiếc ghế tiếp theo.

Đây là một lựa chọn an toàn.

**Trường hợp 2: `p[i] > i`**

Ghế được đánh dấu nằm ở phía trước, tức là một chiếc ghế mà ta chưa đi qua.

Ví dụ:

- Đang ở ghế 2.
- `p[2] = 5`.
- Khi ngồi lên ghế 2, ghế 5 sẽ bị đánh dấu.

Khi di chuyển đến ghế 5, ta sẽ phát hiện ghế đã được đánh dấu và trò chơi kết thúc ngay lập tức.

Điều này khiến ta không thể tiếp tục ngồi lên những chiếc ghế phía sau.

Đây là một lựa chọn không an toàn.

**Nhận xét quan trọng:**

Ta có thể chia các vị trí thành hai nhóm:

| Điều kiện | Ý nghĩa |
|---|---|
| `p[i] ≤ i` | Đánh dấu ghế đã đi qua hoặc ghế hiện tại |
| `p[i] > i` | Đánh dấu một chiếc ghế trong tương lai |

Như vậy, điều quyết định một vị trí có an toàn hay không chính là mối quan hệ giữa `p[i]` và `i`.

### 2.2. Tại sao nên chọn những vị trí có `p[i] ≤ i`?

Hãy xét một ví dụ:

```text
n = 5
p = [4, 3, 2, 5, 1]
```

Ta lần lượt xét từng vị trí:

| Vị trí `i` | `p[i]` | Điều kiện | Có nên ngồi? |
|---|---:|---|---|
| 1 | 4 | 4 > 1 | Không |
| 2 | 3 | 3 > 2 | Không |
| 3 | 2 | 2 ≤ 3 | Có |
| 4 | 5 | 5 > 4 | Không |
| 5 | 1 | 1 ≤ 5 | Có |

Ta có thể lựa chọn:

- Bỏ qua ghế 1.
- Bỏ qua ghế 2.
- Ngồi ghế 3 và đánh dấu ghế 2.
- Bỏ qua ghế 4.
- Ngồi ghế 5 và đánh dấu ghế 1.

Cả ghế 2 và ghế 1 đều đã được đi qua nên việc đánh dấu không gây ảnh hưởng.

Kết quả là ta ngồi được 2 chiếc ghế.

**Nhận xét:**

Những vị trí thỏa mãn `p[i] ≤ i` luôn có thể được chọn mà không làm ảnh hưởng đến các vị trí phía sau.

Ngược lại, nếu `p[i] > i`, việc ngồi lên có thể khiến trò chơi kết thúc sớm.

### 2.3. Tại sao không nên ngồi lên vị trí có `p[i] > i`?

Đây là nhận xét quan trọng để hiểu bản chất Greedy.

Giả sử ta đang ở vị trí `i` và:

```text
p[i] = j
```

với `j > i`.

Nếu ngồi lên ghế `i`, ta sẽ đánh dấu ghế `j`.

Khi đi đến ghế `j`, trò chơi sẽ kết thúc.

Ta có thể nhận thêm 1 chiếc ghế tại vị trí `i`, nhưng đổi lại có nguy cơ mất tất cả những cơ hội ngồi ở các vị trí từ `i + 1` đến `j`.

Đặc biệt, vì `p` là một hoán vị nên mỗi giá trị chỉ xuất hiện đúng một lần.

Nếu `p[i] = j`, thì không có vị trí nào khác đánh dấu ghế `j` thông qua cùng giá trị đó.

Việc lựa chọn ngồi ở vị trí không an toàn không thể giúp tăng số ghế tối đa so với chiến lược chỉ chọn các vị trí an toàn.

Do đó, chiến lược tối ưu là:

- Ngồi tại tất cả vị trí thỏa mãn `p[i] ≤ i`.
- Bỏ qua tất cả vị trí thỏa mãn `p[i] > i`.

---

## 3. Tối ưu ý tưởng bằng Greedy

### 3.1. Nhận ra điều kiện quyết định

Ban đầu, ta có thể nghĩ đến việc:

- Thử ngồi hoặc bỏ qua tại từng chiếc ghế.
- Mô phỏng quá trình đánh dấu.
- Tìm ra cách lựa chọn mang lại số ghế lớn nhất.

Tuy nhiên, mỗi vị trí đều có hai lựa chọn.

Với `n` vị trí, số cách lựa chọn có thể lên đến:

\[
2^n
\]

Đây là cách tiếp cận Brute Force không phù hợp với giới hạn đề bài.

Thay vì thử tất cả các cách, ta cần tìm ra đặc điểm của một lựa chọn tối ưu.

Từ những nhận xét phía trên:

- Nếu `p[i] ≤ i`, việc ngồi không ảnh hưởng đến tương lai.
- Nếu `p[i] > i`, việc ngồi sẽ đánh dấu một ghế chưa được đi qua và có thể kết thúc trò chơi sớm.

Vì vậy, ta chỉ cần đếm số vị trí thỏa mãn:

\[
p[i] \leq i
\]

### 3.2. Ý tưởng Greedy

Thuật toán gồm hai bước:

**Bước 1: Duyệt toàn bộ hoán vị.**

Với mỗi vị trí `i`, kiểm tra điều kiện:

\[
p[i] \leq i
\]

**Bước 2: Đếm số vị trí thỏa mãn.**

- Nếu `p[i] ≤ i`, tăng biến đếm `ans` lên 1.
- Nếu `p[i] > i`, bỏ qua vị trí đó.

Sau khi duyệt hết mảng, `ans` chính là đáp án.

Công thức:

\[
\boxed{ans = \sum_{i=1}^{n}[p[i]\leq i]}
\]

Trong đó, biểu thức trong ngoặc vuông có giá trị:

- 1 nếu điều kiện đúng.
- 0 nếu điều kiện sai.

**Bản chất Greedy:**

Thay vì thử mọi cách lựa chọn, ta luôn ưu tiên những vị trí có thể ngồi mà không gây ảnh hưởng đến các vị trí chưa được thăm.

---

## 4. Mô phỏng thuật toán (Dry Run)

Xét các test case trong ví dụ đề bài.

### 4.1. Ví dụ 1

```text
n = 3
p = [3, 2, 1]
```

Ta xét từng vị trí:

| `i` | `p[i]` | Điều kiện | `ans` |
|---|---:|---|---:|
| 1 | 3 | 3 ≤ 1: Sai | 0 |
| 2 | 2 | 2 ≤ 2: Đúng | 1 |
| 3 | 1 | 1 ≤ 3: Đúng | 2 |

Kết quả:

\[
\boxed{2}
\]

### 4.2. Ví dụ 2

```text
n = 5
p = [4, 3, 2, 5, 1]
```

| `i` | `p[i]` | Điều kiện | `ans` |
|---|---:|---|---:|
| 1 | 4 | 4 ≤ 1: Sai | 0 |
| 2 | 3 | 3 ≤ 2: Sai | 0 |
| 3 | 2 | 2 ≤ 3: Đúng | 1 |
| 4 | 5 | 5 ≤ 4: Sai | 1 |
| 5 | 1 | 1 ≤ 5: Đúng | 2 |

Kết quả:

\[
\boxed{2}
\]

### 4.3. Ví dụ 3

```text
n = 4
p = [4, 2, 1, 3]
```

| `i` | `p[i]` | Điều kiện | `ans` |
|---|---:|---|---:|
| 1 | 4 | 4 ≤ 1: Sai | 0 |
| 2 | 2 | 2 ≤ 2: Đúng | 1 |
| 3 | 1 | 1 ≤ 3: Đúng | 2 |
| 4 | 3 | 3 ≤ 4: Đúng | 3 |

Kết quả:

\[
\boxed{3}
\]

### 4.4. Ví dụ 4

```text
n = 4
p = [2, 3, 4, 1]
```

| `i` | `p[i]` | Điều kiện | `ans` |
|---|---:|---|---:|
| 1 | 2 | 2 ≤ 1: Sai | 0 |
| 2 | 3 | 3 ≤ 2: Sai | 0 |
| 3 | 4 | 4 ≤ 3: Sai | 0 |
| 4 | 1 | 1 ≤ 4: Đúng | 1 |

Kết quả:

\[
\boxed{1}
\]

### 4.5. Tổng hợp Dry Run

| Test case | Hoán vị `p` | Số vị trí `p[i] ≤ i` | Kết quả |
|---|---|---:|---:|
| 1 | `[3, 2, 1]` | 2 | 2 |
| 2 | `[4, 3, 2, 5, 1]` | 2 | 2 |
| 3 | `[4, 2, 1, 3]` | 3 | 3 |
| 4 | `[2, 3, 4, 1]` | 1 | 1 |

---

## 5. Chứng minh tính đúng đắn (Correctness Proof)

Ta cần chứng minh rằng đáp án của bài toán chính là số lượng vị trí thỏa mãn:

\[
p[i] \leq i
\]

### 5.1. Điều kiện đủ (Sufficiency)

Ta chứng minh rằng tất cả các vị trí thỏa mãn `p[i] ≤ i` đều có thể được ngồi.

Xét một vị trí `i` thỏa mãn:

\[
p[i] \leq i
\]

Khi ngồi lên ghế thứ `i`, ta đánh dấu ghế thứ `p[i]`.

Vì:

\[
p[i] \leq i
\]

nên ghế được đánh dấu nằm ở vị trí đã đi qua hoặc chính vị trí hiện tại.

Do đó, việc đánh dấu không ảnh hưởng đến bất kỳ chiếc ghế nào trong tương lai.

Vì vậy, ta có thể ngồi lên tất cả các vị trí thỏa mãn điều kiện này mà không khiến trò chơi kết thúc sớm.

Suy ra số ghế có thể ngồi ít nhất bằng số vị trí thỏa mãn `p[i] ≤ i`.

### 5.2. Điều kiện cần (Necessity)

Ta chứng minh rằng việc ngồi tại các vị trí có `p[i] > i` không thể giúp tạo ra một đáp án lớn hơn.

Xét một vị trí `i` thỏa mãn:

\[
p[i] > i
\]

Đặt:

\[
j=p[i]
\]

Nếu ngồi lên ghế `i`, ghế `j` sẽ bị đánh dấu và trò chơi chắc chắn kết thúc khi đến ghế `j`.

Vì `p` là một hoán vị, chỉ có một vị trí `i` thỏa mãn `p[i]=j`.

Ta có hai trường hợp:

- Nếu `p[j] ≤ j`, ghế `j` vốn là một vị trí an toàn. Ngồi tại `i` khiến ta có thể mất cơ hội ngồi tại `j` và các vị trí an toàn phía sau.
- Nếu `p[j] > j`, ghế `j` không phải vị trí an toàn. Tuy nhiên, việc đánh dấu ghế `j` vẫn có thể khiến ta mất cơ hội ngồi tại những vị trí an toàn nằm phía sau nó.

Nói cách khác, lựa chọn ngồi tại một vị trí không an toàn không thể tạo ra lợi ích lớn hơn việc bỏ qua vị trí đó và tiếp tục chọn những vị trí an toàn.

Do đó, luôn tồn tại một chiến lược tối ưu chỉ ngồi tại các vị trí thỏa mãn `p[i] ≤ i`.

### 5.3. Kết luận

Ta đã chứng minh:

- Tất cả vị trí có `p[i] ≤ i` đều có thể ngồi mà không ảnh hưởng đến tương lai.
- Những vị trí có `p[i] > i` không cần được lựa chọn trong một chiến lược tối ưu.

Vì vậy:

\[
\boxed{ans = \sum_{i=1}^{n}[p[i]\leq i]}
\]

Thuật toán đếm số vị trí thỏa mãn `p[i] ≤ i` là chính xác.

---

## 6. Độ phức tạp (Complexity Analysis)

Giả sử độ dài hoán vị là `n`.

**Time Complexity:**

Ta chỉ cần duyệt mảng một lần.

Tại mỗi vị trí, thực hiện một phép so sánh:

\[
p[i] \leq i
\]

Do đó:

\[
\boxed{O(n)}
\]

Với tổng độ dài các test case không vượt quá `2 × 10^5`, thuật toán đáp ứng tốt giới hạn thời gian.

**Space Complexity:**

Nếu tính cả mảng đầu vào, cần:

\[
O(n)
\]

Bên cạnh mảng đầu vào, thuật toán chỉ sử dụng một biến đếm `ans`.

Vì vậy, **Auxiliary Space Complexity** là:

\[
\boxed{O(1)}
\]

---

## 7. Key Takeaways (Những điều cần rút ra)

1. **Phân tích ảnh hưởng của thao tác:** Khi một hành động tác động đến vị trí khác, cần xác định xem vị trí đó nằm ở quá khứ, hiện tại hay tương lai.

2. **Phân biệt lựa chọn an toàn và không an toàn:** Điều kiện `p[i] ≤ i` cho biết việc ngồi tại vị trí hiện tại không ảnh hưởng đến quá trình di chuyển tiếp theo.

3. **Nhận diện chiến lược Greedy:** Không cần thử mọi cách ngồi hoặc bỏ qua. Ta có thể đưa ra quyết định dựa trên một điều kiện đơn giản tại từng vị trí.

4. **Tận dụng tính chất của Permutation:** Mỗi giá trị chỉ xuất hiện một lần. Tính chất này giúp phân tích mối quan hệ giữa vị trí được chọn và vị trí bị đánh dấu.

5. **Tối ưu từ Brute Force:** Thay vì xét `2^n` cách lựa chọn, ta chỉ cần một lần duyệt mảng với độ phức tạp `O(n)`.

6. **Chú ý chỉ số:** Bài toán sử dụng chỉ số từ 1 đến `n`. Nếu triển khai bằng Python hoặc C++, cần nhớ chuyển đổi chỉ số phù hợp khi truy cập mảng.

---

## 8. Tổng kết (Summary)

Bài toán yêu cầu tìm số lượng ghế lớn nhất có thể ngồi khi đi lần lượt qua một hàng ghế và mỗi lần ngồi sẽ đánh dấu một chiếc ghế khác theo hoán vị `p`.

Nhận xét quan trọng nhất là:

- Nếu `p[i] ≤ i`, chiếc ghế được đánh dấu đã được đi qua hoặc là vị trí hiện tại. Vì vậy, lựa chọn này an toàn.
- Nếu `p[i] > i`, chiếc ghế được đánh dấu nằm ở phía trước và có thể khiến trò chơi kết thúc sớm.
- Do đó, chiến lược tối ưu là chỉ ngồi tại những vị trí thỏa mãn `p[i] ≤ i`.

Công thức cuối cùng:

\[
\boxed{ans = \sum_{i=1}^{n}[p[i]\leq i]}
\]

Chỉ cần duyệt mảng một lần và đếm các vị trí thỏa mãn điều kiện trên.

Đây là một bài toán điển hình về **Greedy + Permutation + Array**, trong đó việc phân tích ảnh hưởng của một thao tác giúp chuyển bài toán từ không gian tìm kiếm rất lớn thành một phép đếm đơn giản với độ phức tạp `O(n)`.