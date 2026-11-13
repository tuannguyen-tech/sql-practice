# Codeforces 2210B – Simply Sitting on Chairs

**Topic:** Greedy, Permutation, Data Structures

**Platform:** Codeforces

**Problem:** Simply Sitting on Chairs

**Difficulty:** 900

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

Trò chơi cũng kết thúc nếu đã đi qua tất cả `n` chiếc ghế.

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

Điều này tạo ra hai trường hợp:

**Trường hợp 1: `p[i] ≤ i`**

Ghế được đánh dấu nằm ở vị trí hiện tại hoặc phía trước vị trí hiện tại.

Ví dụ:

```text
i = 3
p[i] = 2
```

Khi ngồi lên ghế 3, ghế 2 được đánh dấu.

Tuy nhiên, ta đã đi qua ghế 2 rồi.

Vì vậy, việc đánh dấu này không ảnh hưởng đến những chiếc ghế tiếp theo.

Đây là một lựa chọn an toàn.

**Trường hợp 2: `p[i] > i`**

Ghế được đánh dấu nằm ở phía trước, tức là một chiếc ghế mà ta chưa đi qua.

Ví dụ:

```text
i = 2
p[i] = 5
```

Khi ngồi lên ghế 2, ghế 5 sẽ bị đánh dấu.

Khi di chuyển đến ghế 5, ta sẽ phát hiện ghế đã được đánh dấu và trò chơi kết thúc ngay lập tức.

Điều này khiến ta không thể tiếp tục ngồi lên những chiếc ghế phía sau.

Tuy nhiên, không phải tất cả các trường hợp `p[i] > i` đều cần bỏ qua. Điều quan trọng là vị trí được đánh dấu có nằm trước thời điểm trò chơi kết thúc hay không.

### 2.2. Xác định vị trí kết thúc trò chơi

Đây là nhận xét quan trọng trong lời giải.

Giả sử trò chơi kết thúc tại ghế thứ `k`.

Nếu ta đi qua hết tất cả ghế mà không bị dừng lại, ta quy ước `k = n + 1`.

Khi đó, ta chỉ có thể ngồi tại những chiếc ghế có vị trí nhỏ hơn `k`.

Xét một vị trí `i < k`.

Nếu ngồi tại ghế `i`, ta đánh dấu ghế `p[i]`.

Để không khiến trò chơi kết thúc trước ghế `k`, vị trí được đánh dấu phải thỏa mãn một trong hai điều kiện:

- `p[i] ≤ i`: Ghế được đánh dấu đã được đi qua hoặc chính là ghế hiện tại.
- `p[i] ≥ k`: Ghế được đánh dấu nằm tại hoặc phía sau vị trí kết thúc trò chơi.

Ngược lại, nếu:

```text
i < p[i] < k
```

thì ta đánh dấu một chiếc ghế chưa được đi qua và nằm trước vị trí kết thúc dự kiến.

Khi đến chiếc ghế đó, trò chơi sẽ kết thúc sớm hơn `k`.

Như vậy, với một vị trí kết thúc `k`, số ghế tối đa có thể ngồi là số vị trí `i < k` thỏa mãn:

```text
p[i] <= i OR p[i] >= k
```

Ta có thể biểu diễn:

```text
f(k) = số vị trí i < k thỏa mãn:
       p[i] <= i hoặc p[i] >= k
```

Trong đó:

```text
1 <= k <= n + 1
```

### 2.3. Tại sao không cần thử tất cả vị trí kết thúc?

Ban đầu, ta có thể nghĩ rằng cần thử tất cả các giá trị `k` từ `1` đến `n + 1`.

Sau đó, với mỗi `k`, ta đếm số vị trí có thể ngồi.

Tuy nhiên, có một nhận xét quan trọng giúp tối ưu toàn bộ bài toán:

**Luôn tồn tại một chiến lược tối ưu mà trò chơi kết thúc sau khi đi qua tất cả n chiếc ghế.**

Nói cách khác, ta có thể chọn:

```text
k = n + 1
```

Để hiểu tại sao, ta xét một vị trí kết thúc bất kỳ `k ≤ n`.

Gọi `ct` là số vị trí thỏa mãn:

```text
i < k và p[i] >= k
```

Đây là những vị trí mà ta có thể ngồi vì chúng đánh dấu ghế nằm tại hoặc phía sau `k`.

Bây giờ, vì `p` là một hoán vị, mỗi giá trị chỉ xuất hiện đúng một lần.

Có `ct` giá trị nằm trong đoạn `[k, n]` xuất hiện ở các vị trí trước `k`.

Do đó, cũng có đúng `ct` giá trị nhỏ hơn `k` phải xuất hiện tại các vị trí từ `k` đến `n`.

Với những vị trí này:

```text
i >= k
p[i] < k
```

Suy ra:

```text
p[i] <= i
```

Như vậy, phía sau vị trí `k` có ít nhất `ct` vị trí an toàn mà ta có thể ngồi.

Điều này có nghĩa là:

Số ghế có thể ngồi ở phía sau `k` ít nhất bằng số ghế ta có thể ngồi nhờ điều kiện `p[i] >= k` ở phía trước `k`.

Vì vậy, thay vì kết thúc trò chơi tại `k`, ta có thể bỏ qua những vị trí gây kết thúc sớm và tiếp tục chọn các vị trí an toàn phía sau.

Kết quả không bị giảm.

Do đó, lựa chọn tối ưu luôn là:

```text
k = n + 1
```

### 2.4. Tìm điều kiện cuối cùng

Khi:

```text
k = n + 1
```

Ta có:

```text
p[i] >= n + 1
```

là điều không thể xảy ra vì mọi giá trị trong hoán vị đều nằm trong `[1, n]`.

Vì vậy, điều kiện:

```text
p[i] <= i OR p[i] >= k
```

được rút gọn thành:

```text
p[i] <= i
```

Đây chính là nhận xét quyết định của bài toán.

**Kết luận:**

Đáp án là số lượng vị trí thỏa mãn:

```text
p[i] <= i
```

---

## 3. Tối ưu ý tưởng bằng Greedy

### 3.1. Từ Brute Force đến Greedy

Một cách tiếp cận Brute Force ban đầu có thể là:

- Thử tất cả các vị trí kết thúc trò chơi `k`.
- Với mỗi `k`, duyệt các vị trí từ `1` đến `k - 1`.
- Kiểm tra xem có thể ngồi tại vị trí đó hay không.
- Tính tổng số ghế có thể ngồi.
- Lấy giá trị lớn nhất.

Có `n + 1` khả năng kết thúc trò chơi.

Với mỗi khả năng, ta cần duyệt tối đa `n` vị trí.

Do đó, độ phức tạp có thể lên đến:

```text
O(n^2)
```

Với tổng `n` lên đến `2 × 10^5`, cách làm này không phù hợp.

Thay vì thử tất cả các vị trí kết thúc, ta tận dụng nhận xét:

- Luôn tồn tại một chiến lược tối ưu kết thúc tại `n + 1`.
- Khi đó, chỉ những vị trí có `p[i] <= i` mới có thể được chọn.

Nhờ vậy, bài toán được chuyển thành một phép đếm đơn giản.

### 3.2. Ý tưởng Greedy

Ta chỉ cần thực hiện hai bước:

**Bước 1: Duyệt toàn bộ hoán vị.**

Với mỗi vị trí `i`, kiểm tra:

```text
p[i] <= i
```

**Bước 2: Đếm số vị trí thỏa mãn.**

- Nếu `p[i] <= i`, tăng biến đếm `ans` lên 1.
- Nếu `p[i] > i`, bỏ qua vị trí đó.

Sau khi duyệt hết mảng, `ans` chính là đáp án.

Công thức:

```text
ans = count(p[i] <= i)
```

**Bản chất Greedy:**

Ta lựa chọn tất cả các vị trí có thể ngồi mà không gây ảnh hưởng đến quá trình di chuyển trong tương lai.

Thay vì mô phỏng trò chơi với nhiều chiến lược khác nhau, ta sử dụng một điều kiện đơn giản để xác định trực tiếp những vị trí có thể chọn trong một chiến lược tối ưu.

---

## 4. Mô phỏng thuật toán (Dry Run)

Xét các test case trong ví dụ đề bài.

### 4.1. Ví dụ 1

```text
n = 3
p = [3, 2, 1]
```

Ta xét từng vị trí:

| `i` | `p[i]` | Điều kiện `p[i] <= i` | `ans` |
|---|---:|---|---:|
| 1 | 3 | Sai | 0 |
| 2 | 2 | Đúng | 1 |
| 3 | 1 | Đúng | 2 |

Ta có thể ngồi tại ghế 2 và ghế 3.

Kết quả:

```text
2
```

### 4.2. Ví dụ 2

```text
n = 5
p = [4, 3, 2, 5, 1]
```

| `i` | `p[i]` | Điều kiện `p[i] <= i` | `ans` |
|---|---:|---|---:|
| 1 | 4 | Sai | 0 |
| 2 | 3 | Sai | 0 |
| 3 | 2 | Đúng | 1 |
| 4 | 5 | Sai | 1 |
| 5 | 1 | Đúng | 2 |

Ta có thể ngồi tại ghế 3 và ghế 5.

Kết quả:

```text
2
```

### 4.3. Ví dụ 3

```text
n = 4
p = [4, 2, 1, 3]
```

| `i` | `p[i]` | Điều kiện `p[i] <= i` | `ans` |
|---|---:|---|---:|
| 1 | 4 | Sai | 0 |
| 2 | 2 | Đúng | 1 |
| 3 | 1 | Đúng | 2 |
| 4 | 3 | Đúng | 3 |

Ta có thể ngồi tại ghế 2, 3 và 4.

Kết quả:

```text
3
```

### 4.4. Ví dụ 4

```text
n = 4
p = [2, 3, 4, 1]
```

| `i` | `p[i]` | Điều kiện `p[i] <= i` | `ans` |
|---|---:|---|---:|
| 1 | 2 | Sai | 0 |
| 2 | 3 | Sai | 0 |
| 3 | 4 | Sai | 0 |
| 4 | 1 | Đúng | 1 |

Chỉ có ghế thứ 4 thỏa mãn điều kiện.

Kết quả:

```text
1
```

### 4.5. Tổng hợp Dry Run

| Test case | Hoán vị `p` | Số vị trí `p[i] <= i` | Kết quả |
|---|---|---:|---:|
| 1 | `[3, 2, 1]` | 2 | 2 |
| 2 | `[4, 3, 2, 5, 1]` | 2 | 2 |
| 3 | `[4, 2, 1, 3]` | 3 | 3 |
| 4 | `[2, 3, 4, 1]` | 1 | 1 |

---

## 5. Chứng minh tính đúng đắn (Correctness Proof)

Ta cần chứng minh rằng đáp án của bài toán chính là số lượng vị trí thỏa mãn:

```text
p[i] <= i
```

### 5.1. Xác định số ghế tối đa nếu trò chơi kết thúc tại k

Giả sử trò chơi kết thúc tại ghế thứ `k`.

Nếu trò chơi đi qua hết tất cả ghế, ta quy ước `k = n + 1`.

Ta chỉ có thể ngồi tại những vị trí `i < k`.

Để trò chơi không kết thúc trước `k`, nếu ngồi tại ghế `i`, ta phải thỏa mãn một trong hai điều kiện:

```text
p[i] <= i
```

hoặc:

```text
p[i] >= k
```

Nếu `i < p[i] < k`, ta sẽ đánh dấu một chiếc ghế nằm trước `k` nhưng chưa được đi qua. Khi đến chiếc ghế đó, trò chơi sẽ kết thúc.

Do đó, số ghế tối đa khi trò chơi kết thúc tại `k` là:

```text
f(k) = count(i < k và (p[i] <= i hoặc p[i] >= k))
```

### 5.2. Chứng minh lựa chọn k = n + 1 luôn tối ưu

Xét một giá trị bất kỳ `k <= n`.

Gọi `ct` là số vị trí thỏa mãn:

```text
i < k và p[i] >= k
```

Đây là những vị trí có thể ngồi ở phía trước `k` nhờ đánh dấu một chiếc ghế nằm tại hoặc phía sau `k`.

Vì `p` là một hoán vị nên mỗi giá trị từ `1` đến `n` xuất hiện đúng một lần.

Có `ct` giá trị thuộc đoạn `[k, n]` xuất hiện ở các vị trí trước `k`.

Vì vậy, cũng có đúng `ct` giá trị thuộc đoạn `[1, k - 1]` xuất hiện tại các vị trí từ `k` đến `n`.

Xét một vị trí `j >= k` có `p[j] < k`.

Ta luôn có:

```text
p[j] < k <= j
```

Suy ra:

```text
p[j] <= j
```

Như vậy, có ít nhất `ct` vị trí an toàn ở phía sau `k`.

Điều này chứng minh rằng số vị trí thỏa mãn `p[i] <= i` ở phía sau `k` luôn lớn hơn hoặc bằng số vị trí thỏa mãn `p[i] >= k` ở phía trước `k`.

Do đó, nếu thay vì kết thúc tại `k`, ta tiếp tục trò chơi đến cuối cùng và lựa chọn các vị trí an toàn, số ghế có thể ngồi không nhỏ hơn.

Suy ra:

```text
f(n + 1) >= f(k)
```

Vì điều này đúng với mọi `k`, nên lựa chọn `k = n + 1` luôn tối ưu.

### 5.3. Suy ra công thức đáp án

Khi:

```text
k = n + 1
```

Điều kiện:

```text
p[i] >= k
```

không thể xảy ra vì `p[i] <= n`.

Do đó, chỉ còn điều kiện:

```text
p[i] <= i
```

Vậy đáp án chính là số lượng vị trí thỏa mãn điều kiện trên.

```text
ans = count(p[i] <= i)
```

Thuật toán Greedy đếm các vị trí thỏa mãn `p[i] <= i` là chính xác.

---

## 6. Độ phức tạp (Complexity Analysis)

Giả sử độ dài hoán vị là `n`.

**Time Complexity:**

Ta chỉ cần duyệt mảng một lần.

Tại mỗi vị trí, thực hiện một phép so sánh:

```text
p[i] <= i
```

Do đó:

```text
O(n)
```

Với tổng độ dài các test case không vượt quá `2 × 10^5`, thuật toán đáp ứng tốt giới hạn thời gian.

**Space Complexity:**

Nếu tính cả mảng đầu vào, cần:

```text
O(n)
```

Bên cạnh mảng đầu vào, thuật toán chỉ sử dụng một biến đếm `ans`.

Do đó, Auxiliary Space Complexity là:

```text
O(1)
```

---

## 7. Key Takeaways (Những điều cần rút ra)

1. **Phân tích ảnh hưởng của thao tác:** Khi một hành động tác động đến vị trí khác, cần xác định xem vị trí đó nằm ở quá khứ, hiện tại hay tương lai.

2. **Xác định thời điểm kết thúc:** Thay vì chỉ xét việc ngồi hay bỏ qua từng ghế, hãy thử cố định vị trí mà trò chơi kết thúc để tìm ra điều kiện có thể lựa chọn.

3. **Tận dụng tính chất Permutation:** Mỗi giá trị chỉ xuất hiện một lần. Điều này giúp xây dựng lập luận đếm số vị trí giữa hai phía của một ranh giới.

4. **Sử dụng Exchange Argument:** So sánh lợi ích của việc ngồi tại những vị trí trước điểm kết thúc với những vị trí an toàn ở phía sau để chứng minh rằng có thể chọn phương án kết thúc cuối cùng.

5. **Nhận diện chiến lược Greedy:** Không cần thử tất cả các khả năng. Ta có thể tìm được điều kiện quyết định trực tiếp đáp án.

6. **Tối ưu từ Brute Force:** Thay vì thử tất cả vị trí kết thúc với độ phức tạp `O(n^2)`, ta chỉ cần duyệt mảng một lần với độ phức tạp `O(n)`.

---

## 8. Tổng kết (Summary)

Bài toán yêu cầu tìm số lượng ghế lớn nhất có thể ngồi khi đi lần lượt qua một hàng ghế và mỗi lần ngồi sẽ đánh dấu một chiếc ghế khác theo hoán vị `p`.

Nhận xét quan trọng nhất là:

- Nếu `p[i] <= i`, chiếc ghế được đánh dấu đã được đi qua hoặc là vị trí hiện tại. Vì vậy, lựa chọn này không ảnh hưởng đến quá trình di chuyển tiếp theo.
- Nếu `p[i] > i`, chiếc ghế được đánh dấu nằm ở phía trước và có thể khiến trò chơi kết thúc sớm.
- Bằng Exchange Argument và tính chất của hoán vị, ta chứng minh được rằng luôn tồn tại một chiến lược tối ưu đi qua tất cả `n` chiếc ghế.
- Vì vậy, chỉ cần đếm các vị trí thỏa mãn `p[i] <= i`.

Công thức cuối cùng:

```text
ans = count(p[i] <= i)
```

Chỉ cần duyệt mảng một lần và đếm các vị trí thỏa mãn điều kiện trên.

Đây là một bài toán điển hình về **Greedy + Permutation + Exchange Argument**, trong đó việc phân tích điểm kết thúc và tận dụng tính chất hoán vị giúp chuyển một bài toán lựa chọn phức tạp thành một phép đếm đơn giản với độ phức tạp `O(n)`.
