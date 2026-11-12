# Codeforces 2233B – Different Distances

**Topic:** Constructive Algorithms (Thuật toán dựng)  
**Platform:** Codeforces  
**Problem:** Different Distances

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán yêu cầu xây dựng một mảng $a$ có độ dài $4n$, thỏa mãn hai điều kiện:

- Mỗi số nguyên từ $1$ đến $n$ xuất hiện chính xác $4$ lần trong mảng.
- Với mỗi số $x$, gọi $p_{x,1}, p_{x,2}, p_{x,3}, p_{x,4}$ lần lượt là vị trí xuất hiện thứ nhất, thứ hai, thứ ba và thứ tư của $x$.

  Khi đó, ba khoảng cách:

$$
p_{x,2}-p_{x,1}
$$

$$
p_{x,3}-p_{x,2}
$$

$$
p_{x,4}-p_{x,3}
$$

phải đôi một khác nhau.

Nói cách khác, với mỗi số $x$, khoảng cách giữa hai lần xuất hiện liên tiếp của nó không được trùng nhau.

Mục tiêu là xây dựng một mảng thỏa mãn các điều kiện trên.

---

## 2. Phân tích tư duy và nhận xét quan trọng

### 2.1. Hiểu rõ điều kiện khoảng cách

Trước tiên, ta cần hiểu rằng bài toán không yêu cầu các số phải xuất hiện liên tiếp hoặc theo một thứ tự cụ thể.

Điều quan trọng là khoảng cách giữa bốn lần xuất hiện của cùng một số phải tạo thành ba giá trị khác nhau.

Ví dụ, xét mảng:

$$
a=[1,1,2,1,2,3,1,3,2,2,3,3]
$$

Xét số $1$:

- Các vị trí xuất hiện: $1,2,4,7$.
- Ba khoảng cách:

$$
2-1=1
$$

$$
4-2=2
$$

$$
7-4=3
$$

Ta thu được:

$$
[1,2,3]
$$

Ba khoảng cách đôi một khác nhau nên số $1$ thỏa mãn.

Tương tự, số $2$ có các vị trí $3,5,9,10$:

$$
[5-3,9-5,10-9]=[2,4,1]
$$

Số $3$ có các vị trí $6,8,11,12$:

$$
[8-6,11-8,12-11]=[2,3,1]
$$

Cả ba số đều thỏa mãn điều kiện.

### 2.2. Ý tưởng quan trọng: Xây dựng từng block độc lập

Thay vì cố gắng xây dựng toàn bộ mảng cùng một lúc, ta thử tìm một đoạn mảng nhỏ có thể giải quyết được yêu cầu cho một số.

Nếu tìm được một block chứa hai số, trong đó mỗi số xuất hiện đúng bốn lần và có ba khoảng cách đôi một khác nhau, ta có thể sử dụng lại block đó nhiều lần.

Đây chính là ý tưởng của phương pháp xây dựng.

---

## 3. Xây dựng block cơ bản

### 3.1. Xây dựng block cho hai số

Xét hai số bất kỳ $x$ và $y$.

Ta thử xây dựng block:

$$
B=[x,y,y,x,y,x,x,y]
$$

Kiểm tra số lần xuất hiện:

- $x$ xuất hiện tại các vị trí $1,4,6,7$.
- $y$ xuất hiện tại các vị trí $2,3,5,8$.

**Đối với số $x$:**

Các khoảng cách liên tiếp là:

$$
4-1=3
$$

$$
6-4=2
$$

$$
7-6=1
$$

Vậy:

$$
D_x=[3,2,1]
$$

Ba khoảng cách đôi một khác nhau.

**Đối với số $y$:**

Các khoảng cách liên tiếp là:

$$
3-2=1
$$

$$
5-3=2
$$

$$
8-5=3
$$

Vậy:

$$
D_y=[1,2,3]
$$

Ba khoảng cách cũng đôi một khác nhau.

**Kết luận:**

Block:

$$
\boxed{B=[x,y,y,x,y,x,x,y]}
$$

giải quyết hoàn toàn yêu cầu cho cả hai số $x$ và $y$.

### 3.2. Tại sao có thể ghép nhiều block?

Giả sử ta có hai block:

$$
B_1=[x,y,y,x,y,x,x,y]
$$

$$
B_2=[u,v,v,u,v,u,u,v]
$$

Ta nối chúng lại:

$$
B=B_1+B_2
$$

Khi đó:

- $x,y$ chỉ xuất hiện trong $B_1$.
- $u,v$ chỉ xuất hiện trong $B_2$.
- Các vị trí xuất hiện của mỗi số đều nằm trọn trong block tương ứng.

Việc nối thêm block phía sau chỉ làm thay đổi vị trí tuyệt đối của các phần tử trong block, chứ không làm thay đổi khoảng cách giữa các lần xuất hiện của chúng.

Vì vậy, mỗi block vẫn giữ nguyên tính chất hợp lệ.

Đây là nhận xét quan trọng giúp ta xây dựng mảng có kích thước bất kỳ.

---

## 4. Xử lý hai trường hợp của n

Sau khi tìm được block cho hai số, ta chia bài toán thành hai trường hợp dựa vào tính chẵn lẻ của $n$.

### 4.1. Trường hợp 1: n chẵn

Nếu $n$ chẵn, ta có thể chia toàn bộ các số thành từng cặp:

$$
(1,2),(3,4),(5,6),\ldots,(n-1,n)
$$

Với mỗi cặp $(x,y)$, ta sử dụng block:

$$
[x,y,y,x,y,x,x,y]
$$

Ví dụ, với $n=4$:

Cặp thứ nhất:

$$
B_1=[1,2,2,1,2,1,1,2]
$$

Cặp thứ hai:

$$
B_2=[3,4,4,3,4,3,3,4]
$$

Nối hai block lại:

$$
\begin{aligned}
a=[&1,2,2,1,2,1,1,2,\\
&3,4,4,3,4,3,3,4]
\end{aligned}
$$

Ta có:

- Mỗi số từ $1$ đến $4$ xuất hiện đúng bốn lần.
- Mỗi số có ba khoảng cách liên tiếp là $3,2,1$ hoặc $1,2,3$.
- Ba khoảng cách luôn đôi một khác nhau.

Vì vậy, cách xây dựng này hoạt động với mọi $n$ chẵn.

### 4.2. Trường hợp 2: n lẻ

Nếu $n$ lẻ, ta không thể chia tất cả các số thành từng cặp.

Ví dụ, với $n=5$, ta có:

$$
1,2,3,4,5
$$

Nếu ghép từng cặp, ta sẽ còn dư một số.

Vì vậy, ta cần tìm một block riêng để xử lý ba số đầu tiên, sau đó những số còn lại tiếp tục được ghép thành từng cặp.

Ta sử dụng block:

$$
\boxed{
B_0=[1,1,2,1,2,3,1,3,2,2,3,3]
}
$$

Kiểm tra từng số:

**Đối với số 1:**

Các vị trí xuất hiện:

$$
[1,2,4,7]
$$

Các khoảng cách:

$$
[1,2,3]
$$

**Đối với số 2:**

Các vị trí xuất hiện:

$$
[3,5,9,10]
$$

Các khoảng cách:

$$
[2,4,1]
$$

**Đối với số 3:**

Các vị trí xuất hiện:

$$
[6,8,11,12]
$$

Các khoảng cách:

$$
[2,3,1]
$$

Cả ba số đều có ba khoảng cách đôi một khác nhau.

Sau khi xử lý xong ba số đầu tiên, ta còn các số:

$$
4,5,6,\ldots,n
$$

Vì $n$ lẻ nên số lượng các số còn lại là:

$$
n-3
$$

Đây là một số chẵn, vì vậy ta có thể chia chúng thành từng cặp:

$$
(4,5),(6,7),\ldots,(n-1,n)
$$

Với mỗi cặp, tiếp tục sử dụng block:

$$
[x,y,y,x,y,x,x,y]
$$

**Ví dụ với $n=5$:**

Ta sử dụng block cho ba số đầu tiên:

$$
B_0=[1,1,2,1,2,3,1,3,2,2,3,3]
$$

Sau đó, ghép thêm block cho cặp $(4,5)$:

$$
B_1=[4,5,5,4,5,4,4,5]
$$

Mảng cuối cùng là:

$$
a=B_0+B_1
$$

Hay:

$$
\begin{aligned}
a=[&1,1,2,1,2,3,1,3,2,2,3,3,\\
&4,5,5,4,5,4,4,5]
\end{aligned}
$$

Mảng có đúng $4n=20$ phần tử và mỗi số từ $1$ đến $5$ xuất hiện đúng bốn lần.

---

## 5. Tổng kết chiến lược xây dựng

Ta có thể tổng hợp cách xây dựng thành hai trường hợp:

**Trường hợp n chẵn:**

Chia các số thành từng cặp:

$$
(1,2),(3,4),\ldots,(n-1,n)
$$

Mỗi cặp sử dụng block:

$$
[x,y,y,x,y,x,x,y]
$$

**Trường hợp n lẻ:**

- Đầu tiên, sử dụng block $B_0$ để xử lý ba số $1,2,3$.
- Sau đó, chia các số còn lại thành từng cặp.
- Mỗi cặp tiếp tục sử dụng block:

$$
[x,y,y,x,y,x,x,y]
$$

Như vậy, ta không cần tìm cách xây dựng riêng cho từng giá trị $n$. Chỉ cần hai loại block là có thể xử lý tất cả trường hợp hợp lệ.

---

## 6. Chứng minh tính đúng đắn (Correctness Proof)

Ta cần chứng minh mảng được xây dựng luôn thỏa mãn hai điều kiện của đề bài.

### 6.1. Mỗi số xuất hiện đúng bốn lần

Đối với trường hợp $n$ chẵn:

- Mỗi cặp $(x,y)$ sử dụng một block.
- Trong block, cả $x$ và $y$ đều xuất hiện đúng bốn lần.
- Mỗi số chỉ thuộc duy nhất một cặp.

Do đó, mỗi số từ $1$ đến $n$ xuất hiện đúng bốn lần.

Đối với trường hợp $n$ lẻ:

- Block $B_0$ chứa các số $1,2,3$, mỗi số xuất hiện đúng bốn lần.
- Các số còn lại được chia thành từng cặp.
- Trong mỗi block của một cặp, mỗi số cũng xuất hiện đúng bốn lần.

Vì các block không sử dụng chung giá trị nên mỗi số từ $1$ đến $n$ xuất hiện đúng bốn lần.

### 6.2. Ba khoảng cách luôn đôi một khác nhau

Đối với block hai số:

$$
B=[x,y,y,x,y,x,x,y]
$$

Ta đã chứng minh:

$$
D_x=[3,2,1]
$$

$$
D_y=[1,2,3]
$$

Cả hai dãy đều có ba giá trị đôi một khác nhau.

Đối với block $B_0$:

- Số $1$ có các khoảng cách $[1,2,3]$.
- Số $2$ có các khoảng cách $[2,4,1]$.
- Số $3$ có các khoảng cách $[2,3,1]$.

Tất cả đều thỏa mãn điều kiện.

Ngoài ra, khi nối các block, các vị trí của cùng một số vẫn nằm trong block ban đầu. Việc dịch chuyển toàn bộ vị trí của một block không làm thay đổi khoảng cách giữa các lần xuất hiện.

Vì vậy, việc ghép các block không ảnh hưởng đến tính hợp lệ của từng số.

**Kết luận:**

Mảng được xây dựng luôn có đúng $4n$ phần tử, mỗi số xuất hiện đúng bốn lần và ba khoảng cách liên tiếp của mỗi số đôi một khác nhau.

Do đó, thuật toán luôn tạo ra một đáp án hợp lệ.

---

## 7. Độ phức tạp (Complexity Analysis)

Ta xét hai trường hợp:

- Nếu $n$ chẵn, ta tạo $n/2$ block, mỗi block có $8$ phần tử.
- Nếu $n$ lẻ, ta tạo một block ban đầu có $12$ phần tử và $(n-3)/2$ block, mỗi block có $8$ phần tử.

Trong cả hai trường hợp, tổng số phần tử được tạo ra là:

$$
4n
$$

Mỗi phần tử chỉ được thêm vào mảng đúng một lần.

**Time Complexity:**

$$
\boxed{O(n)}
$$

**Space Complexity:**

$$
\boxed{O(n)}
$$

Ta sử dụng một vector để lưu mảng kết quả có $4n$ phần tử.

---

## 8. Key Takeaways (Những điều cần rút ra)

1. **Tìm block cơ bản:** Thay vì xây dựng toàn bộ đáp án cùng lúc, hãy thử tìm một đoạn nhỏ có thể giải quyết hoàn toàn yêu cầu cho một nhóm phần tử.

2. **Tận dụng tính độc lập:** Nếu mỗi giá trị chỉ xuất hiện trong một block riêng biệt thì ta có thể nối các block mà không làm thay đổi khoảng cách giữa các lần xuất hiện.

3. **Chia trường hợp chẵn lẻ:** Khi số lượng phần tử không thể chia đều thành từng cặp, hãy thử xử lý một nhóm nhỏ riêng rồi ghép phần còn lại.

4. **Kiểm tra bằng vị trí:** Với bài toán yêu cầu khoảng cách giữa các lần xuất hiện, hãy liệt kê vị trí trước rồi tính hiệu giữa hai vị trí liên tiếp.

5. **Tư duy Constructive Algorithms:** Không nhất thiết phải tìm ra một đáp án duy nhất. Chỉ cần xây dựng được một đáp án thỏa mãn tất cả điều kiện của đề bài.

---

## 9. Tổng kết (Summary)

Bài toán yêu cầu xây dựng một mảng có độ dài $4n$, trong đó mỗi số xuất hiện đúng bốn lần và ba khoảng cách giữa các lần xuất hiện liên tiếp phải đôi một khác nhau.

Ý tưởng quan trọng nhất là tìm được block:

$$
\boxed{[x,y,y,x,y,x,x,y]}
$$

Block này giải quyết hoàn toàn yêu cầu cho hai số bất kỳ.

Sau đó:

- Nếu $n$ chẵn, chia tất cả các số thành từng cặp và sử dụng block trên.
- Nếu $n$ lẻ, sử dụng block riêng cho ba số đầu tiên, rồi chia các số còn lại thành từng cặp.

Đây là một ví dụ điển hình của **Constructive Algorithms**: tìm ra một cấu trúc nhỏ hợp lệ, chứng minh tính chất của nó, rồi ghép các cấu trúc lại để tạo ra đáp án cho bài toán lớn hơn.