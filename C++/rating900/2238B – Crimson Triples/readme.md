# Codeforces 2238B – Crimson Triples

**Topic:** Number Theory, Combinatorics  
**Platform:** Codeforces  
**Problem:** Crimson Triples

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán yêu cầu đếm số bộ ba số nguyên dương $(a,b,c)$ thỏa mãn:

- $1 \le a,b,c \le n$
- $\gcd(\text{lcm}(a,b), \text{lcm}(b,c)) = \gcd(a,c)$

Trong đó:

- $\gcd(x,y)$: Ước chung lớn nhất của hai số.
- $\text{lcm}(x,y)$: Bội chung nhỏ nhất của hai số.

Mục tiêu là tìm tổng số bộ ba $(a,b,c)$ thỏa mãn điều kiện trên.

---

## 2. Phân tích tư duy và nhận xét toán học

### 2.1. Quan sát biểu thức đề bài

Ta có điều kiện:

$$
\gcd(\text{lcm}(a,b), \text{lcm}(b,c)) = \gcd(a,c)
$$

Quan sát biểu thức, ta nhận thấy số $b$ xuất hiện trong cả hai phép tính LCM:

- $\text{lcm}(a,b)$
- $\text{lcm}(b,c)$

Điều này gợi ý rằng ta nên xem xét vai trò của $b$ trong hai phép tính trên.

Nhớ lại tính chất của LCM:
- Nếu $a$ chia hết cho $b$ (ký hiệu $b \mid a$) thì $\text{lcm}(a,b)=a$.
- Nếu $c$ chia hết cho $b$ (ký hiệu $b \mid c$) thì $\text{lcm}(b,c)=c$.

Nếu cả hai điều kiện cùng đúng, biểu thức ban đầu trở thành:

$$
\gcd(a,c)=\gcd(a,c)
$$

Vì vậy, ta có một nhận xét:

**Nếu $a$ chia hết cho $b$ và $c$ chia hết cho $b$, thì bộ ba $(a,b,c)$ chắc chắn thỏa mãn điều kiện đề bài.**

Từ đây, ta đặt ra giả thuyết rằng điều kiện đề bài tương đương với:

$$
a \text{ chia hết cho } b \quad \text{và} \quad c \text{ chia hết cho } b
$$

Tuy nhiên, đây mới chỉ là nhận xét ban đầu. Ta cần chứng minh cả hai chiều để khẳng định giả thuyết này.

### 2.2. Chứng minh chiều thuận

Giả sử:

$$
a \text{ chia hết cho } b \quad \text{và} \quad c \text{ chia hết cho } b
$$

Vì $a$ chia hết cho $b$ ($b \mid a$), nên:

$$
\text{lcm}(a,b)=a
$$

Tương tự, vì $c$ chia hết cho $b$ ($b \mid c$), nên:

$$
\text{lcm}(b,c)=c
$$

Thay vào biểu thức ban đầu:

$$
\begin{aligned}
&\gcd(\text{lcm}(a,b), \text{lcm}(b,c)) \\
&= \gcd(a,c)
\end{aligned}
$$

Vậy nếu $a$ và $c$ đều chia hết cho $b$, điều kiện bài toán luôn đúng.

### 2.3. Chứng minh chiều ngược lại

Bây giờ, ta cần chứng minh rằng nếu điều kiện đề bài đúng thì bắt buộc:

$$
a \text{ chia hết cho } b \quad \text{và} \quad c \text{ chia hết cho } b
$$

Giả sử:

$$
\gcd(\text{lcm}(a,b), \text{lcm}(b,c)) = \gcd(a,c)
$$

**Bước 1: Chứng minh $a$ chia hết cho $b$ ($b \mid a$).**

Theo định nghĩa của LCM, LCM là bội chung của hai số. Do đó:

$$
b \mid \text{lcm}(a,b)
$$

và:

$$
b \mid \text{lcm}(b,c)
$$

Như vậy, $b$ là ước chung của hai số trong phép GCD ở vế trái.

Theo tính chất của GCD, mọi ước chung của hai số đều là ước của GCD của chúng. Suy ra:

$$
b \mid \gcd(\text{lcm}(a,b), \text{lcm}(b,c))
$$

Mà theo giả thiết:

$$
\gcd(\text{lcm}(a,b), \text{lcm}(b,c)) = \gcd(a,c)
$$

Nên:

$$
b \mid \gcd(a,c)
$$

Tiếp theo, theo định nghĩa GCD, ước chung lớn nhất của $a$ và $c$ phải là ước của cả hai số. Do đó:

$$
\gcd(a,c) \mid a
$$

Ta có:

$$
b \mid \gcd(a,c)
$$

và:

$$
\gcd(a,c) \mid a
$$

Theo tính chất bắc cầu của phép chia hết, suy ra:

$$
\boxed{b \mid a \quad (\text{hay } a \text{ chia hết cho } b)}
$$

**Bước 2: Chứng minh $c$ chia hết cho $b$ ($b \mid c$).**

Tương tự, ta đã có:

$$
b \mid \gcd(a,c)
$$

Mà theo định nghĩa GCD:

$$
\gcd(a,c) \mid c
$$

Áp dụng tính chất bắc cầu của phép chia hết:

$$
\boxed{b \mid c \quad (\text{hay } c \text{ chia hết cho } b)}
$$

### 2.4. Kết luận

Ta đã chứng minh được cả hai chiều:

- Nếu $a$ và $c$ đều chia hết cho $b$, điều kiện đề bài luôn đúng.
- Nếu điều kiện đề bài đúng, thì $a$ và $c$ bắt buộc phải chia hết cho $b$.

Vậy:

$$
\boxed{
\gcd(\text{lcm}(a,b), \text{lcm}(b,c))
= \gcd(a,c)
\iff
a \text{ chia hết cho } b \text{ và } c \text{ chia hết cho } b
}
$$

**Ý nghĩa:** Thay vì phải tính GCD và LCM cho từng bộ ba, ta chỉ cần đếm những bộ ba mà $a$ và $c$ đều là bội của $b$.

Đây chính là bước biến đổi quan trọng giúp đưa bài toán về một bài toán đếm đơn giản hơn.

---

## 3. Xây dựng công thức đếm

Sau khi biến đổi điều kiện, bài toán trở thành:

Đếm số bộ ba $(a,b,c)$ thỏa mãn:

$$
1 \le a,b,c \le n
$$

và:

$$
a \text{ chia hết cho } b,\quad c \text{ chia hết cho } b
$$

### 3.1. Tại sao cố định $b$ trước?

Ta nhận thấy $b$ xuất hiện trong cả hai điều kiện chia hết. Vì vậy, thay vì chọn đồng thời cả ba biến, ta cố định $b$ trước.

Khi đã biết $b$, việc chọn $a$ và $c$ trở nên độc lập:

- Chọn $a$ trong các bội của $b$ không vượt quá $n$.
- Chọn $c$ trong các bội của $b$ không vượt quá $n$.

Ta có thể đếm số cách chọn từng biến rồi nhân chúng lại.

### 3.2. Đếm số cách chọn $a$

Vì $a$ phải chia hết cho $b$, các giá trị hợp lệ của $a$ là:

$$
a \in \{b,2b,3b,\ldots,kb\}
$$

Trong đó, $k$ là số nguyên lớn nhất thỏa mãn:

$$
kb \le n
$$

Chia cả hai vế cho $b$:

$$
k \le \frac{n}{b}
$$

Vì $k$ là số nguyên lớn nhất thỏa mãn điều kiện, nên:

$$
k = \left\lfloor \frac{n}{b} \right\rfloor
$$

Do đó, số cách chọn $a$ là:

$$
\boxed{\left\lfloor \frac{n}{b} \right\rfloor}
$$

### 3.3. Đếm số cách chọn $c$

Tương tự, $c$ cũng phải là bội của $b$ và không vượt quá $n$.

Vì vậy, số cách chọn $c$ cũng là:

$$
\boxed{\left\lfloor \frac{n}{b} \right\rfloor}
$$

### 3.4. Đếm số cặp $(a,c)$

Khi đã cố định $b$:

- Có $\left\lfloor \frac{n}{b} \right\rfloor$ cách chọn $a$.
- Có $\left\lfloor \frac{n}{b} \right\rfloor$ cách chọn $c$.

Hai lựa chọn độc lập với nhau, nên theo nguyên lý nhân:

$$
\begin{aligned}
\text{Số cặp }(a,c)
&= \left\lfloor \frac{n}{b} \right\rfloor
\times \left\lfloor \frac{n}{b} \right\rfloor \\
&= \left\lfloor \frac{n}{b} \right\rfloor^2
\end{aligned}
$$

### 3.5. Công thức tổng quát

Ta cần xét tất cả các giá trị của $b$ từ $1$ đến $n$.

Với mỗi giá trị $b$, số bộ ba hợp lệ là:

$$
\left\lfloor \frac{n}{b} \right\rfloor^2
$$

Cộng số bộ ba của tất cả các giá trị $b$, ta thu được:

$$
\boxed{
\text{Answer} =
\sum_{b=1}^{n}
\left\lfloor \frac{n}{b} \right\rfloor^2
}
$$

Đây là công thức cuối cùng của bài toán.

---

## 4. Ví dụ minh họa (Dry Run)

Giả sử:

$$
n=5
$$

Ta xét từng giá trị của $b$.

| $b$ | Các bội của $b$ không vượt quá $n$ | Số cách chọn $a$ | Số cách chọn $c$ | Số bộ ba |
|---|---|---:|---:|---:|
| 1 | 1, 2, 3, 4, 5 | 5 | 5 | 25 |
| 2 | 2, 4 | 2 | 2 | 4 |
| 3 | 3 | 1 | 1 | 1 |
| 4 | 4 | 1 | 1 | 1 |
| 5 | 5 | 1 | 1 | 1 |

Với $b=1$:

$$
5 \times 5 = 25
$$

Với $b=2$:

$$
2 \times 2 = 4
$$

Với $b=3,4,5$, mỗi giá trị $b$ có đúng một cách chọn $a$ và một cách chọn $c$.

Tổng số bộ ba hợp lệ là:

$$
25+4+1+1+1=32
$$

Vậy:

$$
\boxed{\text{Answer}=32}
$$

---

## 5. Chứng minh tính đúng đắn (Correctness Proof)

Ta đã chứng minh được điều kiện ban đầu tương đương với:

$$
a \text{ chia hết cho } b \quad \text{và} \quad c \text{ chia hết cho } b
$$

Xét một giá trị $b$ bất kỳ trong đoạn $[1,n]$.

- Có chính xác $\left\lfloor \frac{n}{b} \right\rfloor$ cách chọn $a$.
- Có chính xác $\left\lfloor \frac{n}{b} \right\rfloor$ cách chọn $c$.
- Hai lựa chọn độc lập nên có chính xác $\left\lfloor \frac{n}{b} \right\rfloor^2$ cặp $(a,c)$.

Mỗi bộ ba $(a,b,c)$ chỉ có một giá trị $b$ xác định. Vì vậy, khi duyệt tất cả $b$ từ $1$ đến $n$, mỗi bộ ba hợp lệ được đếm đúng một lần.

Do đó, công thức:

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

Với mỗi giá trị $b$, chỉ thực hiện các phép tính cơ bản:

- Phép chia nguyên `n / b`.
- Phép nhân để tính bình phương.
- Phép cộng vào kết quả.

**Time Complexity:**

$$
\boxed{O(n)}
$$

**Space Complexity:**

$$
\boxed{O(1)}
$$

Thuật toán chỉ sử dụng một số biến để lưu giá trị $n$, $b$ và đáp án, không cần thêm mảng hay cấu trúc dữ liệu phụ.

---

## 7. Key Takeaways (Những điều cần rút ra)

1. **Quan sát biểu thức toán học:** Chú ý những biến xuất hiện lặp lại trong biểu thức để tìm ra hướng biến đổi.

2. **Sử dụng tính chất GCD và LCM:** LCM là bội chung của hai số, còn GCD là ước chung lớn nhất của hai số.

3. **Chứng minh hai chiều:** Khi muốn khẳng định hai điều kiện tương đương, cần chứng minh cả chiều thuận và chiều ngược lại.

4. **Cố định một biến:** Khi đã cố định $b$, việc chọn $a$ và $c$ trở nên độc lập, giúp đơn giản hóa bài toán đếm.

5. **Nguyên lý nhân:** Khi hai lựa chọn độc lập, số cách kết hợp bằng tích số cách của từng lựa chọn.

6. **Floor Division:** Số lượng bội dương của $b$ không vượt quá $n$ là:

$$
\left\lfloor \frac{n}{b} \right\rfloor
$$

Trong C++, phép chia hai số nguyên `n / b` chính là phép lấy phần nguyên này.

---

## 8. Tổng kết (Summary)

Bài toán ban đầu sử dụng GCD và LCM nên nhìn có vẻ phức tạp. Tuy nhiên, thay vì tính trực tiếp hai phép toán này cho từng bộ ba, ta tìm cách biến đổi điều kiện toán học.

Bước quan trọng nhất là chứng minh:

$$
\gcd(\text{lcm}(a,b), \text{lcm}(b,c))
= \gcd(a,c)
$$

khi và chỉ khi:

$$
a \text{ chia hết cho } b \quad \text{và} \quad c \text{ chia hết cho } b
$$

Sau đó, ta cố định $b$, đếm số bội của $b$ không vượt quá $n$, rồi áp dụng nguyên lý nhân.

Công thức cuối cùng:

$$
\boxed{
\text{Answer} =
\sum_{b=1}^{n}
\left\lfloor \frac{n}{b} \right\rfloor^2
}
$$

**Bài học quan trọng:** Hãy tìm cách đơn giản hóa điều kiện toán học trước khi nghĩ đến thuật toán. Một nhận xét toán học đúng có thể biến một bài toán tưởng như phức tạp thành một bài toán đếm rất đơn giản.
