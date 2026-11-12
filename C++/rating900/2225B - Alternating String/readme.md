# Codeforces 2225B – Alternating String

**Topic:** Greedy, Brute Force, Strings  
**Platform:** Codeforces  
**Problem:** Alternating String  
**Difficulty:** 900

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán cho một chuỗi $s$ chỉ chứa hai ký tự `a` và `b`.

Một chuỗi được gọi là **Alternating String** nếu hai ký tự đứng cạnh nhau luôn khác nhau.

Điều kiện:

$$
s_i \neq s_{i+1}
$$

với mọi $1 \leq i < n$.

Ví dụ:

- `ababab`: Hợp lệ.
- `bababa`: Hợp lệ.
- `aabb`: Không hợp lệ.
- `aaabb`: Không hợp lệ.

Ta được phép thực hiện tối đa một lần thao tác:

1. Chọn một đoạn con liên tiếp $[l,r]$.
2. Có thể đảo ngược tất cả ký tự trong đoạn: `a` thành `b`, `b` thành `a`. Thao tác này không bắt buộc.
3. Bắt buộc đảo ngược thứ tự các ký tự trong đoạn đã chọn.

Yêu cầu của bài toán là xác định xem có thể biến chuỗi ban đầu thành một Alternating String bằng tối đa một lần thao tác hay không.

**Output:**

- In `YES` nếu có thể tạo được Alternating String.
- In `NO` nếu không thể.

---

## 2. Phân tích tư duy và nhận xét quan trọng

### 2.1. Xác định điều kiện để chuỗi hợp lệ

Trước tiên, ta cần hiểu rõ điều kiện của một Alternating String.

Hai ký tự đứng cạnh nhau phải luôn khác nhau.

Có 4 trường hợp khi xét một cặp ký tự:

| Cặp ký tự | Trạng thái |
|---|---|
| `ab` | Hợp lệ |
| `ba` | Hợp lệ |
| `aa` | Không hợp lệ |
| `bb` | Không hợp lệ |

Như vậy, vấn đề của chuỗi chỉ nằm ở những cặp ký tự liên tiếp giống nhau.

Ta gọi những cặp này là **Bad Pairs (cặp xấu)**.

Ví dụ:

$$
s = \text{"aabbabaa"}
$$

Các cặp ký tự liên tiếp:

| Vị trí | Cặp ký tự | Trạng thái |
|---|---|---|
| 1–2 | `aa` | Bad |
| 2–3 | `ab` | Good |
| 3–4 | `bb` | Bad |
| 4–5 | `ba` | Good |
| 5–6 | `ab` | Good |
| 6–7 | `aa` | Bad |
| 7–8 | `aa` | Bad |

Tổng cộng có 4 Bad Pairs.

**Nhận xét:** Thay vì quan tâm toàn bộ chuỗi, ta chỉ cần tập trung vào số lượng cặp ký tự liên tiếp giống nhau.

### 2.2. Phân tích ảnh hưởng của thao tác đảo ngược

Đây là nhận xét quan trọng nhất của bài toán.

Ta được phép chọn một đoạn con, có thể đảo ngược tất cả ký tự bên trong, sau đó bắt buộc đảo ngược thứ tự của đoạn.

Hãy xét hai đặc điểm.

**1. Các cặp ký tự nằm hoàn toàn bên trong đoạn không thay đổi tính chất.**

Ví dụ:

$$
\text{"aabb"} \rightarrow \text{"bbaa"}
$$

Ta thấy:

- `aa` vẫn là cặp hai ký tự giống nhau.
- `bb` vẫn là cặp hai ký tự giống nhau.
- `ab` và `ba` vẫn là các cặp hai ký tự khác nhau.

Điều này xảy ra vì khi đảo ngược thứ tự:

- `ab` trở thành `ba`.
- `ba` trở thành `ab`.
- `aa` vẫn là `aa`.
- `bb` vẫn là `bb`.

Nếu thực hiện thêm thao tác đảo ký tự (`a` thành `b` và ngược lại), tính chất giống hoặc khác nhau của mỗi cặp vẫn được bảo toàn.

Do đó:

**Đảo ngược một đoạn không thể thay đổi tính chất của các cặp nằm hoàn toàn bên trong đoạn.**

**2. Chỉ có hai cặp ở hai đầu đoạn có thể thay đổi tính chất.**

Giả sử chọn đoạn $[l,r]$.

Trước khi thao tác:

$$
s_{l-1} \quad | \quad s_l \ldots s_r \quad | \quad s_{r+1}
$$

Sau khi đảo ngược đoạn:

$$
s_{l-1} \quad | \quad s_r \ldots s_l \quad | \quad s_{r+1}
$$

Hai cặp tiếp giáp với đoạn được chọn có thể thay đổi:

- Cặp bên trái: $(s_{l-1},s_l)$.
- Cặp bên phải: $(s_r,s_{r+1})$.

Sau thao tác, chúng trở thành:

- Cặp bên trái: $(s_{l-1},s_r)$.
- Cặp bên phải: $(s_l,s_{r+1})$.

Như vậy, chỉ có tối đa hai cặp ký tự có thể thay đổi tính chất giống hoặc khác nhau.

**Nhận xét quan trọng:**

$$
\boxed{\text{Một lần thao tác chỉ có thể thay đổi tối đa 2 Bad Pairs.}}
$$

### 2.3. Tìm điều kiện để có thể tạo Alternating String

Từ nhận xét trên, ta chia thành hai trường hợp.

**Trường hợp 1: Có nhiều hơn 2 Bad Pairs.**

Giả sử chuỗi ban đầu có 3 Bad Pairs.

Vì một lần thao tác chỉ có thể thay đổi tối đa hai cặp ký tự, nên ít nhất vẫn còn một Bad Pair sau thao tác.

Điều đó có nghĩa là chuỗi vẫn tồn tại hai ký tự liên tiếp giống nhau.

Do đó, không thể tạo được Alternating String.

Ta có:

$$
bad > 2 \Rightarrow NO
$$

**Trường hợp 2: Có tối đa 2 Bad Pairs.**

Ta có thể chọn một đoạn phù hợp để đưa các cặp xấu đến hai ranh giới của đoạn được chọn.

Sau đó, sử dụng thao tác đảo ký tự nếu cần để khiến các cặp ở ranh giới trở thành các cặp khác nhau.

Vì vậy, tất cả Bad Pairs đều có thể được xử lý trong một lần thao tác.

Ta có:

$$
bad \leq 2 \Rightarrow YES
$$

Kết hợp hai trường hợp:

$$
\boxed{ans = YES \iff bad \leq 2}
$$

Đây là điều kiện quan trọng nhất của bài toán.

### 2.4. Tại sao phải đếm Bad Pairs thay vì đếm số ký tự giống nhau?

Xét hai chuỗi:

$$
s_1=\text{"aaaa"}
$$

$$
s_2=\text{"aabb"}
$$

Chuỗi thứ nhất có 4 ký tự `a`, chuỗi thứ hai có 2 ký tự `a` và 2 ký tự `b`.

Tuy nhiên, điều quyết định khả năng biến đổi không phải là số lượng ký tự `a` hay `b`, mà là số cặp ký tự liên tiếp giống nhau.

Với `aaaa`:

$$
bad=3
$$

Với `aabb`:

$$
bad=2
$$

Do đó:

- `aaaa` có đáp án `NO`.
- `aabb` có đáp án `YES`.

**Nhận xét:** Trong những bài toán về chuỗi, cần xác định chính xác điều kiện vi phạm thay vì chỉ đếm số lượng từng loại ký tự.

---

## 3. Tối ưu ý tưởng bằng Greedy

### 3.1. Từ thao tác ban đầu đến nhận xét Greedy

Một cách tiếp cận Brute Force ban đầu có thể là:

- Thử tất cả các đoạn con $[l,r]$.
- Đảo ngược đoạn đã chọn.
- Thử cả trường hợp đảo ký tự và không đảo ký tự.
- Kiểm tra chuỗi sau thao tác có alternating hay không.

Tuy nhiên, số đoạn con của chuỗi có độ dài $n$ là:

$$
\frac{n(n+1)}{2}
$$

Do đó, số trường hợp cần thử có độ phức tạp:

$$
O(n^2)
$$

Nếu mỗi trường hợp còn phải kiểm tra lại toàn bộ chuỗi thì độ phức tạp có thể lên đến $O(n^3)$.

Với giới hạn tổng độ dài chuỗi lên đến $2 \cdot 10^5$, cách làm này không phù hợp.

Thay vì mô phỏng tất cả thao tác, ta tận dụng nhận xét quan trọng:

- Các cặp bên trong đoạn không thay đổi tính chất.
- Chỉ hai cặp ở ranh giới có thể thay đổi.
- Một lần thao tác chỉ có thể xử lý tối đa 2 Bad Pairs.

Vì vậy, không cần thử từng đoạn con.

### 3.2. Ý tưởng Greedy

Ta chỉ cần thực hiện hai việc:

**Bước 1: Đếm số Bad Pairs.**

Duyệt tất cả các cặp ký tự liên tiếp trong chuỗi.

Mỗi khi:

$$
s_i=s_{i+1}
$$

ta tăng số lượng Bad Pairs lên 1.

**Bước 2: Kiểm tra điều kiện.**

Sau khi duyệt toàn bộ chuỗi:

- Nếu số Bad Pairs không vượt quá 2, đáp án là `YES`.
- Nếu số Bad Pairs lớn hơn 2, đáp án là `NO`.

Công thức:

$$
\boxed{
ans =
\begin{cases}
YES & \text{nếu } bad \leq 2\\
NO & \text{nếu } bad > 2
\end{cases}
}
$$

**Bản chất Greedy:** Thay vì tìm kiếm trực tiếp đoạn con cần đảo ngược, ta tận dụng giới hạn khả năng của một lần thao tác để đưa ra quyết định ngay từ số lượng Bad Pairs.

---

## 4. Mô phỏng thuật toán (Dry Run)

Xét các chuỗi:

$$
s_1=\text{"abbaba"}
$$

$$
s_2=\text{"aaaaa"}
$$

$$
s_3=\text{"aabb"}
$$

### 4.1. Ví dụ 1: `abbaba`

Các cặp ký tự liên tiếp:

| Vị trí | Cặp | Trạng thái |
|---|---|---|
| 1–2 | `ab` | Good |
| 2–3 | `bb` | Bad |
| 3–4 | `ba` | Good |
| 4–5 | `ab` | Good |
| 5–6 | `ba` | Good |

Ta có:

$$
bad=1
$$

Vì:

$$
1 \leq 2
$$

Kết quả:

$$
\boxed{YES}
$$

### 4.2. Ví dụ 2: `aaaaa`

Các cặp ký tự liên tiếp:

| Vị trí | Cặp | Trạng thái |
|---|---|---|
| 1–2 | `aa` | Bad |
| 2–3 | `aa` | Bad |
| 3–4 | `aa` | Bad |
| 4–5 | `aa` | Bad |

Ta có:

$$
bad=4
$$

Vì:

$$
4 > 2
$$

Một lần thao tác không thể xử lý hết 4 Bad Pairs.

Kết quả:

$$
\boxed{NO}
$$

### 4.3. Ví dụ 3: `aabb`

Các cặp ký tự liên tiếp:

| Vị trí | Cặp | Trạng thái |
|---|---|---|
| 1–2 | `aa` | Bad |
| 2–3 | `ab` | Good |
| 3–4 | `bb` | Bad |

Ta có:

$$
bad=2
$$

Vì:

$$
2 \leq 2
$$

Kết quả:

$$
\boxed{YES}
$$

Ta có thể chọn đoạn từ vị trí 2 đến vị trí 3:

$$
\text{"aabb"} \rightarrow \text{"abab"}
$$

Chuỗi sau thao tác đã alternating.

### 4.4. Tổng hợp Dry Run

| Chuỗi | Số Bad Pairs | Điều kiện | Kết quả |
|---|---:|---|---|
| `abbaba` | 1 | $1 \leq 2$ | YES |
| `aaaaa` | 4 | $4 > 2$ | NO |
| `aabb` | 2 | $2 \leq 2$ | YES |
| `ababa` | 0 | $0 \leq 2$ | YES |
| `abbaabba` | 3 | $3 > 2$ | NO |
| `bbb` | 2 | $2 \leq 2$ | YES |

---

## 5. Chứng minh tính đúng đắn (Correctness Proof)

Ta cần chứng minh điều kiện:

$$
bad \leq 2
$$

là điều kiện cần và đủ để bài toán có đáp án `YES`.

### 5.1. Điều kiện cần (Necessity)

Giả sử chuỗi ban đầu có $bad$ Bad Pairs.

Khi chọn một đoạn con để đảo ngược:

- Các cặp nằm hoàn toàn bên trong đoạn giữ nguyên tính chất.
- Các cặp nằm hoàn toàn bên ngoài đoạn cũng giữ nguyên tính chất.
- Chỉ có tối đa hai cặp ở ranh giới đoạn có thể thay đổi tính chất.

Vì vậy, một lần thao tác không thể xử lý nhiều hơn 2 Bad Pairs.

Nếu:

$$
bad > 2
$$

thì sau thao tác vẫn còn ít nhất một Bad Pair.

Do đó, chuỗi không thể trở thành Alternating String.

Suy ra:

$$
\boxed{bad \leq 2}
$$

là điều kiện cần.

### 5.2. Điều kiện đủ (Sufficiency)

Ta chứng minh rằng nếu có tối đa 2 Bad Pairs thì luôn tồn tại một thao tác phù hợp.

**Trường hợp 1: Không có Bad Pair.**

Chuỗi đã alternating từ đầu.

Không cần thực hiện thao tác.

**Trường hợp 2: Có đúng 1 Bad Pair.**

Giả sử Bad Pair nằm giữa vị trí $i$ và $i+1$:

$$
s_i=s_{i+1}
$$

Ta chọn đoạn:

$$
[i+1,n]
$$

Sau khi đảo ngược đoạn, ký tự đầu tiên của đoạn sẽ là ký tự ban đầu ở vị trí $n$.

Ta có thể chọn đảo hoặc không đảo ký tự trong đoạn để đảm bảo ký tự tại vị trí $i+1$ khác ký tự tại vị trí $i$.

Các cặp bên trong đoạn vốn không có Bad Pair nên vẫn hợp lệ.

Như vậy, ta xử lý được toàn bộ chuỗi.

**Trường hợp 3: Có đúng 2 Bad Pairs.**

Giả sử hai Bad Pairs nằm tại vị trí $i$ và $j$, với $i < j$.

Ta có:

$$
s_i=s_{i+1}
$$

và:

$$
s_j=s_{j+1}
$$

Ta chọn đoạn:

$$
[i+1,j]
$$

Sau khi đảo ngược đoạn:

- Cặp bên trái trở thành $(s_i,s_j)$.
- Cặp bên phải trở thành $(s_{i+1},s_{j+1})$.

Vì hai cặp ban đầu đều là Bad Pairs:

$$
s_i=s_{i+1}
$$

$$
s_j=s_{j+1}
$$

Ta có thể lựa chọn thao tác đảo ký tự hoặc không đảo ký tự để đảm bảo cả hai cặp ở ranh giới đều trở thành Good Pairs.

Các cặp nằm hoàn toàn bên trong đoạn không thay đổi tính chất.

Vì vậy, toàn bộ chuỗi trở thành Alternating String.

### 5.3. Kết luận

Ta đã chứng minh:

- Nếu $bad > 2$, không thể tạo Alternating String.
- Nếu $bad \leq 2$, luôn có thể tạo Alternating String.

Do đó:

$$
\boxed{ans = YES \iff bad \leq 2}
$$

Thuật toán đếm Bad Pairs và kiểm tra điều kiện `bad <= 2` là chính xác.

---

## 6. Độ phức tạp (Complexity Analysis)

Giả sử độ dài chuỗi là $n$.

**Time Complexity:**

Ta chỉ cần duyệt chuỗi từ trái sang phải một lần.

Tại mỗi vị trí, thực hiện một phép so sánh hai ký tự liên tiếp.

Do đó:

$$
\boxed{O(n)}
$$

Với tổng độ dài tất cả test case không vượt quá $2 \cdot 10^5$, thuật toán đáp ứng tốt giới hạn thời gian.

**Space Complexity:**

Ta chỉ cần một biến đếm số Bad Pairs.

Không cần tạo thêm mảng hoặc cấu trúc dữ liệu phụ thuộc vào độ dài chuỗi.

Do đó:

$$
\boxed{O(1)}
$$

---

## 7. Key Takeaways (Những điều cần rút ra)

1. **Xác định điều kiện không hợp lệ:** Với Alternating String, những cặp ký tự liên tiếp giống nhau chính là các vị trí vi phạm.

2. **Phân tích ảnh hưởng của thao tác:** Thay vì mô phỏng toàn bộ thao tác đảo ngược, hãy tìm xem thao tác thực sự làm thay đổi những phần nào của dữ liệu.

3. **Nhận ra tính bất biến (Invariant):** Những cặp ký tự nằm hoàn toàn bên trong đoạn được chọn không thay đổi tính chất giống hoặc khác nhau sau khi đảo ngược và đảo ký tự.

4. **Giới hạn khả năng của thao tác:** Một lần đảo ngược đoạn chỉ có thể thay đổi tối đa hai cặp ở ranh giới.

5. **Chuyển nhận xét thành điều kiện:** Từ giới hạn hai ranh giới, ta suy ra chỉ có thể xử lý tối đa 2 Bad Pairs.

6. **Chứng minh điều kiện cần và đủ:** Không chỉ chứng minh có hơn 2 cặp xấu thì không thể, mà còn phải chứng minh có tối đa 2 cặp xấu thì luôn tìm được đoạn phù hợp.

7. **Tránh Brute Force không cần thiết:** Không phải lúc nào cũng cần thử tất cả các thao tác. Phân tích tính chất của thao tác có thể giúp tìm ra điều kiện quyết định trực tiếp đáp án.

---

## 8. Tổng kết (Summary)

Bài toán yêu cầu xác định xem có thể biến một chuỗi chỉ gồm `a` và `b` thành Alternating String bằng tối đa một lần thao tác đảo ngược đoạn hay không.

Ý tưởng quan trọng nhất là nhận ra:

- Những cặp ký tự nằm bên trong đoạn được chọn không thay đổi tính chất giống hoặc khác nhau.
- Chỉ hai cặp nằm ở ranh giới đoạn có thể thay đổi.
- Vì vậy, một lần thao tác chỉ có thể xử lý tối đa 2 Bad Pairs.

Từ đó, ta có điều kiện:

$$
\boxed{ans = YES \iff bad \leq 2}
$$

Thay vì mô phỏng tất cả các đoạn con, ta chỉ cần đếm số cặp ký tự liên tiếp giống nhau và kiểm tra xem số lượng đó có vượt quá 2 hay không.

Đây là một ví dụ điển hình về việc kết hợp **Greedy + String + Invariant**: phân tích bản chất của thao tác để tìm ra điều kiện quyết định đáp án, thay vì thử tất cả các khả năng.