# Codeforces 2232B – Cake Leveling

**Topic:** Greedy, Math, Prefix Sum, Binary Search  
**Platform:** Codeforces  
**Problem:** Cake Leveling  
**Difficulty:** 900

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán cho một mảng $a$ gồm $n$ phần tử, trong đó $a_i$ biểu diễn chiều cao lớp kem tại vị trí thứ $i$ trên chiếc bánh.

Alice đặt một con dao ở độ cao nguyên $h$, sau đó kéo dao từ trái sang phải để làm phẳng lớp kem.

Quy tắc hoạt động:

- Nếu chiều cao kem tại vị trí $i$ lớn hơn $h$, phần kem dư sẽ được đẩy sang vị trí $i+1$.
- Nếu chiều cao kem tại vị trí $i$ nhỏ hơn hoặc bằng $h$, vị trí đó không có kem dư để đẩy sang bên phải.
- Phần kem dư tại vị trí cuối cùng sẽ bị đẩy ra khỏi chiếc bánh.

Yêu cầu của bài toán là tìm chiều cao nguyên lớn nhất $h$ sao cho sau khi thực hiện thao tác trên, tất cả các vị trí từ $1$ đến $i$ đều có chiều cao bằng nhau.

Cần tính đáp án cho tất cả các prefix:

$$
[1], [1,2], [1,2,3], \ldots, [1,2,\ldots,n]
$$

**Output:** In ra $n$ số nguyên, trong đó số thứ $i$ là chiều cao lớn nhất có thể đạt được khi làm phẳng $i$ vị trí đầu tiên.

---

## 2. Phân tích tư duy và nhận xét quan trọng

### 2.1. Hiểu rõ bản chất thao tác

Điều quan trọng đầu tiên là hiểu rằng kem chỉ có thể di chuyển theo một chiều:

$$
1 \rightarrow 2 \rightarrow 3 \rightarrow \ldots \rightarrow n
$$

Không có thao tác nào cho phép kem di chuyển ngược từ phải sang trái.

Điều này có nghĩa là:

- Những vị trí phía trước không thể nhận thêm kem từ các vị trí phía sau.
- Nếu một prefix phía trước không đủ lượng kem để đạt chiều cao $h$, những prefix phía sau cũng không thể khắc phục được vấn đề đó.

Vì vậy, ta không thể chỉ xét tổng lượng kem của prefix hiện tại mà bỏ qua các prefix trước đó.

### 2.2. Tìm điều kiện để một chiều cao $h$ hợp lệ

Giả sử ta muốn làm phẳng $i$ vị trí đầu tiên với chiều cao $h$.

Khi tất cả $i$ vị trí đều có chiều cao $h$, tổng lượng kem cần thiết là:

$$
i \times h
$$

Gọi tổng lượng kem ban đầu của prefix thứ $i$ là:

$$
S_i=a_1+a_2+\ldots+a_i
$$

Tuy nhiên, chỉ kiểm tra điều kiện:

$$
S_i \geq i \times h
$$

là chưa đủ.

Bởi vì kem chỉ di chuyển từ trái sang phải, nên mỗi prefix nhỏ hơn cũng phải có đủ lượng kem để đạt chiều cao $h$.

Do đó, với mọi prefix thứ $k$ thỏa mãn $1 \leq k \leq i$, ta cần:

$$
S_k \geq k \times h
$$

Biến đổi bất đẳng thức:

$$
h \leq \frac{S_k}{k}
$$

Vì $h$ là số nguyên, ta có:

$$
h \leq \left\lfloor \frac{S_k}{k} \right\rfloor
$$

Điều kiện này phải đúng với tất cả các prefix từ $1$ đến $i$.

Vì vậy, chiều cao lớn nhất có thể chọn là:

$$
\boxed{
ans_i=\min_{1\leq k\leq i}
\left\lfloor\frac{S_k}{k}\right\rfloor
}
$$

Đây là công thức quan trọng nhất của bài toán.

### 2.3. Tại sao phải lấy giá trị nhỏ nhất (MIN)?

Xét ví dụ:

$$
a=[4,2,3]
$$

Tính tổng và trung bình của từng prefix:

| Prefix | Tổng prefix | Trung bình nguyên |
|---|---:|---:|
| $[4]$ | 4 | 4 |
| $[4,2]$ | 6 | 3 |
| $[4,2,3]$ | 9 | 3 |

Ta có:

- Prefix thứ nhất có chiều cao tối đa là $4$.
- Prefix thứ hai có chiều cao tối đa là $3$.
- Prefix thứ ba có chiều cao tối đa là $3$.

Vì vậy:

$$
ans_1=4
$$

$$
ans_2=\min(4,3)=3
$$

$$
ans_3=\min(4,3,3)=3
$$

**Tại sao không lấy trung bình của prefix hiện tại để làm đáp án?**

Xét ví dụ:

$$
a=[2,100]
$$

Trung bình của toàn bộ prefix là:

$$
\frac{2+100}{2}=51
$$

Nhưng vị trí đầu tiên chỉ có $2$ đơn vị kem và không thể nhận thêm kem từ vị trí thứ hai.

Do đó, chiều cao lớn nhất mà cả hai vị trí có thể đạt được là:

$$
ans_2=\min(2,51)=2
$$

Nhận xét quan trọng:

**Một prefix phía trước có thể trở thành giới hạn chiều cao cho tất cả các prefix phía sau.**

---

## 3. Tối ưu công thức bằng Greedy

### 3.1. Từ công thức toán học đến thuật toán

Ta đã tìm được công thức:

$$
ans_i=\min_{1\leq k\leq i}
\left\lfloor\frac{S_k}{k}\right\rfloor
$$

Một cách tiếp cận trực tiếp là:

- Với mỗi vị trí $i$, tính tổng prefix.
- Duyệt lại tất cả các prefix từ $1$ đến $i$.
- Tìm giá trị trung bình nguyên nhỏ nhất.

Tuy nhiên, cách này có độ phức tạp:

$$
O(n^2)
$$

Với giới hạn $n \leq 2 \cdot 10^5$, cách làm này không tối ưu.

Vậy ta cần tìm cách không phải duyệt lại những prefix đã xử lý.

### 3.2. Nhận xét quan trọng: Chỉ cần lưu hai biến

Khi chuyển từ prefix thứ $i-1$ sang prefix thứ $i$, ta chỉ cần duy trì hai thông tin:

**1. `sum`:**

Lưu tổng các phần tử từ vị trí đầu tiên đến vị trí hiện tại.

$$
sum=S_i
$$

**2. `ans`:**

Lưu giá trị nhỏ nhất của trung bình nguyên trong tất cả các prefix đã duyệt.

$$
ans=\min_{1\leq k\leq i}
\left\lfloor\frac{S_k}{k}\right\rfloor
$$

Khi đọc thêm phần tử $a_i$, ta thực hiện ba bước:

**Bước 1:** Cập nhật tổng prefix.

$$
sum=sum+a_i
$$

**Bước 2:** Tính trung bình nguyên của prefix hiện tại.

$$
avg=\left\lfloor\frac{sum}{i}\right\rfloor
$$

**Bước 3:** Cập nhật đáp án bằng cách lấy giá trị nhỏ nhất.

$$
\boxed{ans=\min(ans,avg)}
$$

Sau đó, in ra `ans`.

Đây chính là ý tưởng Greedy của bài toán.

Thay vì tính lại toàn bộ các prefix, ta chỉ cần giữ lại kết quả tốt nhất đã tìm được và cập nhật khi xuất hiện một giá trị nhỏ hơn.

---

## 4. Mô phỏng thuật toán (Dry Run)

Xét mảng:

$$
a=[3,3,3,1,1]
$$

Ban đầu:

- `sum = 0`
- `ans = INF`

Ta duyệt mảng từ trái sang phải.

| $i$ | $a_i$ | `sum` | `avg = sum / i` | `ans` |
|---|---:|---:|---:|---:|
| 1 | 3 | 3 | 3 | 3 |
| 2 | 3 | 6 | 3 | 3 |
| 3 | 3 | 9 | 3 | 3 |
| 4 | 1 | 10 | 2 | 2 |
| 5 | 1 | 11 | 2 | 2 |

Kết quả:

$$
\boxed{[3,3,3,2,2]}
$$

### Phân tích bước cập nhật quan trọng

Tại vị trí thứ $4$:

Trước đó:

$$
ans=3
$$

Khi thêm phần tử $a_4=1$:

$$
sum=3+3+3+1=10
$$

Tính trung bình nguyên:

$$
avg=\left\lfloor\frac{10}{4}\right\rfloor=2
$$

Cập nhật đáp án:

$$
ans=\min(3,2)=2
$$

Tại vị trí thứ $5$:

$$
sum=11
$$

$$
avg=\left\lfloor\frac{11}{5}\right\rfloor=2
$$

Do đó:

$$
ans=\min(2,2)=2
$$

**Nhận xét:** Đáp án chỉ có thể giữ nguyên hoặc giảm xuống, không thể tăng trở lại vì mỗi bước đều lấy giá trị nhỏ nhất với đáp án trước đó.

---

## 5. Chứng minh tính đúng đắn (Correctness Proof)

Ta chứng minh thuật toán bằng quy nạp.

### 5.1. Cơ sở quy nạp (Base Case)

Với prefix đầu tiên:

$$
S_1=a_1
$$

Chiều cao lớn nhất có thể đạt được chính là:

$$
ans_1=\left\lfloor\frac{S_1}{1}\right\rfloor=a_1
$$

Điều này hoàn toàn đúng vì chỉ có một vị trí và không cần di chuyển kem.

### 5.2. Bước quy nạp (Inductive Step)

Giả sử đáp án tại prefix thứ $i-1$ đã đúng:

$$
ans_{i-1}=
\min_{1\leq k\leq i-1}
\left\lfloor\frac{S_k}{k}\right\rfloor
$$

Khi thêm phần tử $a_i$, tổng prefix mới là:

$$
S_i=S_{i-1}+a_i
$$

Để prefix thứ $i$ đạt chiều cao $h$, ta cần đồng thời thỏa mãn:

- Tất cả điều kiện của những prefix trước đó.
- Điều kiện của prefix hiện tại.

Vì vậy:

$$
ans_i=
\min\left(
ans_{i-1},
\left\lfloor\frac{S_i}{i}\right\rfloor
\right)
$$

Đây chính xác là phép cập nhật mà thuật toán thực hiện.

Do đó, nếu đáp án của prefix thứ $i-1$ đúng thì đáp án của prefix thứ $i$ cũng đúng.

### 5.3. Kết luận

Theo nguyên lý quy nạp, thuật toán tính đúng đáp án cho tất cả các prefix từ $1$ đến $n$.

---

## 6. Độ phức tạp (Complexity Analysis)

Ta duyệt mảng từ trái sang phải đúng một lần.

Tại mỗi vị trí, ta chỉ thực hiện:

- Một phép cộng để cập nhật tổng.
- Một phép chia để tính trung bình nguyên.
- Một phép so sánh để cập nhật đáp án.

Mỗi thao tác đều có độ phức tạp $O(1)$.

**Time Complexity:**

$$
\boxed{O(n)}
$$

**Space Complexity:**

$$
\boxed{O(1)}
$$

Ta chỉ cần sử dụng hai biến `sum` và `ans`, không cần lưu toàn bộ mảng.

Lưu ý: Nên sử dụng kiểu dữ liệu `long long` cho tổng prefix vì mỗi phần tử có thể đạt tới $10^9$.

---

## 7. Key Takeaways (Những điều cần rút ra)

1. **Tư duy từ thao tác sang toán học:** Thay vì mô phỏng trực tiếp việc đẩy kem, hãy tìm điều kiện về tổng lượng kem cần thiết để đạt chiều cao $h$.

2. **Không chỉ xét prefix hiện tại:** Vì dữ liệu chỉ di chuyển từ trái sang phải, mọi prefix trước đó đều có thể giới hạn chiều cao của prefix hiện tại.

3. **Nhận ra công thức MIN:** Đáp án là giá trị trung bình nguyên nhỏ nhất trong tất cả các prefix đã xuất hiện.

4. **Tận dụng kết quả trước đó:** Khi chuyển sang prefix mới, không cần tính lại những prefix cũ. Chỉ cần duy trì `sum` và `ans`.

5. **Tư duy Greedy:** Mỗi bước chỉ cần lấy giá trị nhỏ hơn giữa đáp án hiện tại và trung bình nguyên của prefix mới.

6. **Tối ưu độ phức tạp:** Một công thức toán học phù hợp có thể giúp biến cách làm $O(n^2)$ thành $O(n)$.

---

## 8. Tổng kết (Summary)

Bài toán yêu cầu tìm chiều cao lớn nhất có thể đạt được khi làm phẳng từng prefix của mảng.

Ý tưởng quan trọng nhất là nhận ra rằng mọi prefix trước đó đều phải có đủ lượng kem để đạt chiều cao $h$.

Từ đó, ta thu được công thức:

$$
\boxed{
ans_i=\min_{1\leq k\leq i}
\left\lfloor\frac{S_k}{k}\right\rfloor
}
$$

Thay vì duyệt lại tất cả các prefix, ta chỉ cần duy trì hai biến:

- `sum`: Tổng các phần tử đã duyệt.
- `ans`: Giá trị trung bình nguyên nhỏ nhất đã gặp.

Mỗi khi đọc một phần tử mới, ta cập nhật tổng, tính trung bình nguyên và lấy MIN với đáp án trước đó.

Đây là một ví dụ điển hình về việc kết hợp **Math + Prefix Sum + Greedy** để tìm ra lời giải tối ưu với độ phức tạp $O(n)$.