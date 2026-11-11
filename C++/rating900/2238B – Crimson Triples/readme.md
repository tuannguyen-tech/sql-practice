# Codeforces 2238B – Crimson Triples

**Topic:** Number Theory, Combinatorics  
**Platform:** Codeforces  
**Problem:** Crimson Triples

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán yêu cầu đếm số bộ ba số nguyên dương $(a,b,c)$ thỏa mãn:

- $1 \le a,b,c \le n$
- $\gcd(\operatorname{lcm}(a,b), \operatorname{lcm}(b,c)) = \gcd(a,c)$

Trong đó:

- $\gcd(x,y)$: Ước chung lớn nhất của hai số.
- $\operatorname{lcm}(x,y)$: Bội chung nhỏ nhất của hai số.

Mục tiêu là tìm số lượng bộ ba $(a,b,c)$ thỏa mãn điều kiện trên.

---

## 2. Phân tích tư duy và nhận xét toán học

### 2.1. Nhận xét quan trọng

Ta cần chứng minh rằng:

$$
\gcd(\operatorname{lcm}(a,b), \operatorname{lcm}(b,c)) = \gcd(a,c)
$$

tương đương với hai điều kiện:

$$
b \mid a
$$

và

$$
b \mid c
$$

Nói cách khác, một bộ ba $(a,b,c)$ hợp lệ khi và chỉ khi $a$ và $c$ đều chia hết cho $b$.

### 2.2. Chứng minh chiều thứ nhất

Giả sử:

$$
b \mid a \quad \text{và} \quad b \mid c
$$

Vì $b$ là ước của $a$, nên:

$$
\operatorname{lcm}(a,b) = a
$$

Tương tự:

$$
\operatorname{lcm}(b,c) = c
$$

Thay vào biểu thức ban đầu:

$$
\begin{aligned}
&\gcd(\operatorname{lcm}(a,b), \operatorname{lcm}(b,c)) \\
&= \gcd(a,c)
\end{aligned}
$$

Vậy nếu $b$ chia hết $a$ và $c$, điều kiện bài toán luôn đúng.

### 2.3. Chứng minh chiều ngược lại

Giả sử điều kiện bài toán đúng:

$$
\gcd(\operatorname{lcm}(a,b), \operatorname{lcm}(b,c)) = \gcd(a,c)
$$

Ta cần chứng minh:

$$
b \mid a \quad \text{và} \quad b \mid c
$$

**Bước 1: Chứng minh $b \mid a$.**

Giả sử ngược lại:

$$
b \nmid a
$$

Ta có:

$$
b \mid \operatorname{lcm}(a,b)
$$

và:

$$
b \mid \operatorname{lcm}(b,c)
$$

Vì $b$ là ước chung của hai số trên, nên:

$$
b \mid \gcd(\operatorname{lcm}(a,b), \operatorname{lcm}(b,c))
$$

Theo điều kiện đề bài:

$$
b \mid \gcd(a,c)
$$

Mà ước chung lớn nhất luôn là ước của từng số, nên:

$$
\gcd(a,c) \mid a
$$

Suy ra:

$$
b \mid a
$$

Điều này mâu thuẫn với giả sử ban đầu $b \nmid a$.

Vậy:

$$
b \mid a
$$

**Bước 2: Chứng minh $b \mid c$.**

Tương tự, giả sử:

$$
b \nmid c
$$

Từ lập luận trên, ta cũng suy ra:

$$
b \mid \gcd(a,c)
$$

Mà:

$$
\gcd(a,c) \mid c
$$

Nên:

$$
b \mid c
$$

Điều này mâu thuẫn với giả sử ban đầu.

Vậy:

$$
b \mid c
$$

**Kết luận:**

Điều kiện ban đầu tương đương với:

$$
\boxed{b \mid a \quad \text{và} \quad b \mid c}
$$

---

## 3. Chiến lược đếm số bộ ba

Sau khi chứng minh được điều kiện tương đương, ta không cần tính `gcd` hay `lcm` nữa.

Bài toán trở thành:

Đếm số bộ ba $(a,b,c)$ sao cho:

$$
1 \le a,b,c \le n
$$

và:

$$
b \mid a,\quad b \mid c
$$

### 3.1. Cố định giá trị $b$

Ta xét từng giá trị của $b$ từ $1$ đến $n$.

Khi đã cố định $b$, ta cần chọn:

- $a$ là một bội của $b$.
- $c$ là một bội của $b$.

### 3.2. Đếm số cách chọn $a$

Các giá trị hợp lệ của $a$ là:

$$
b, 2b, 3b, \ldots, kb
$$

Vì $a \le n$, ta có:

$$
kb \le n
$$

Suy ra:

$$
k \le \frac{n}{b}
$$

Do đó, số lượng giá trị hợp lệ của $a$ là:

$$
\boxed{\left\lfloor \frac{n}{b} \right\rfloor}
$$

Trong C++, phép chia số nguyên `n / b` tự động lấy phần nguyên.

### 3.3. Đếm số cách chọn cặp $(a,c)$

Tương tự, $c$ cũng có:

$$
\left\lfloor \frac{n}{b} \right\rfloor
$$

cách lựa chọn.

Vì việc chọn $a$ và chọn $c$ độc lập với nhau, số cặp $(a,c)$ là:

$$
\left\lfloor \frac{n}{b} \right\rfloor
\times
\left\lfloor \frac{n}{b} \right\rfloor
$$

Hay:

$$
\boxed{\left\lfloor \frac{n}{b} \right\rfloor^2}
$$

### 3.4. Công thức tổng quát

Ta xét tất cả giá trị của $b$ từ $1$ đến $n$.

Với mỗi $b$, số bộ ba hợp lệ là:

$$
\left\lfloor \frac{n}{b} \right\rfloor^2
$$

Vậy đáp án cuối cùng là:

$$
\boxed{
\text{Answer} =
\sum_{b=1}^{n}
\left\lfloor \frac{n}{b} \right\rfloor^2
}
$$

---

## 4. Ví dụ minh họa (Dry Run)

Giả sử:

$$
n = 5
$$

Ta xét lần lượt từng giá trị của $b$.

| $b$ | Các bội của $b$ không vượt quá $n$ | Số cách chọn $a$ | Số cách chọn $c$ | Số bộ ba |
|---|---|---:|---:|---:|
| 1 | 1, 2, 3, 4, 5 | 5 | 5 | 25 |
| 2 | 2, 4 | 2 | 2 | 4 |
| 3 | 3 | 1 | 1 | 1 |
| 4 | 4 | 1 | 1 | 1 |
| 5 | 5 | 1 | 1 | 1 |

Tổng số bộ ba hợp lệ:

$$
25 + 4 + 1 + 1 + 1 = 32
$$

Vậy:

$$
\boxed{\text{Answer} = 32}
$$

---

## 5. Chứng minh tính đúng đắn (Correctness Proof)

Ta đã chứng minh được rằng điều kiện ban đầu của bài toán tương đương với:

$$
b \mid a \quad \text{và} \quad b \mid c
$$

Xét một giá trị $b$ bất kỳ trong đoạn $[1,n]$.

- Có chính xác $\left\lfloor \frac{n}{b} \right\rfloor$ cách chọn $a$ là bội của $b$ và không vượt quá $n$.
- Có chính xác $\left\lfloor \frac{n}{b} \right\rfloor$ cách chọn $c$ thỏa mãn điều kiện tương tự.
- Hai lựa chọn độc lập nên có chính xác $\left\lfloor \frac{n}{b} \right\rfloor^2$ cặp $(a,c)$.

Mỗi bộ ba hợp lệ có duy nhất một giá trị $b$, do đó khi xét tất cả $b$ từ $1$ đến $n$, ta đếm được mỗi bộ ba đúng một lần.

Vì vậy, công thức:

$$
\boxed{
\sum_{b=1}^{n}
\left\lfloor \frac{n}{b} \right\rfloor^2
}
$$

đếm chính xác tất cả các bộ ba thỏa mãn yêu cầu bài toán.

---

## 6. Độ phức tạp (Complexity Analysis)

Ta duyệt $b$ từ $1$ đến $n$.

Với mỗi giá trị $b$, chỉ thực hiện một số phép tính cơ bản:

- Phép chia nguyên `n / b`.
- Phép nhân để tính bình phương.
- Phép cộng vào kết quả.

Do đó:

**Time Complexity:**

$$
\boxed{O(n)}
$$

**Space Complexity:**

$$
\boxed{O(1)}
$$

Ta chỉ sử dụng một số biến để lưu giá trị $n$, $b$ và đáp án, không cần thêm mảng hay cấu trúc dữ liệu phụ.

---

## 7. Key Takeaways (Những điều cần rút ra)

1. **Biến đổi điều kiện toán học:** Không nên vội vàng tính trực tiếp `gcd` và `lcm`. Hãy tìm cách biến đổi điều kiện để phát hiện bản chất của bài toán.

2. **Sử dụng phản chứng:** Khi cần chứng minh chiều ngược lại, có thể giả sử kết luận sai rồi tìm ra mâu thuẫn.

3. **Cố định một biến:** Khi một biến xuất hiện trong nhiều điều kiện, hãy thử cố định biến đó để đơn giản hóa việc đếm.

4. **Nguyên lý nhân:** Khi hai lựa chọn độc lập, tổng số cách kết hợp bằng tích số cách của từng lựa chọn.

5. **Floor Division:** Biểu thức `n / b` trong C++ với hai toán hạng nguyên chính là phần nguyên của phép chia, tương ứng với:

$$
\left\lfloor \frac{n}{b} \right\rfloor
$$

---

## 8. Tổng kết (Summary)

Bài toán ban đầu trông khá phức tạp vì sử dụng cả `gcd` và `lcm`.

Tuy nhiên, điểm mấu chốt là chứng minh được:

$$
\gcd(\operatorname{lcm}(a,b), \operatorname{lcm}(b,c))
= \gcd(a,c)
$$

khi và chỉ khi:

$$
b \mid a \quad \text{và} \quad b \mid c
$$

Sau đó, ta cố định $b$, đếm số bội của $b$ không vượt quá $n$, rồi áp dụng nguyên lý nhân để thu được công thức:

$$
\boxed{
\text{Answer} =
\sum_{b=1}^{n}
\left\lfloor \frac{n}{b} \right\rfloor^2
}
$$

Đây là ví dụ điển hình cho cách giải một bài toán đếm bằng cách **biến đổi toán học trước, sau đó mới tìm công thức đếm**.