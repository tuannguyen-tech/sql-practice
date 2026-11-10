# Codeforces 2254B – Evanescent

**Topic:** Constructive Algorithms (Thuật toán dựng)  
**Platform:** Codeforces  
**Problem:** Yet Another Constructive

---

## 1. Tổng quan bài toán (Problem Statement)

Bài toán yêu cầu xây dựng một mảng `a` gồm `n` số nguyên dương sao cho thỏa mãn hai điều kiện:

**Input:** Ba số nguyên `n, k, m`.

**Yêu cầu:**

- Mảng `a = [a₁, a₂, ..., aₙ]` gồm `n` số nguyên dương (`aᵢ > 0`).
- Tồn tại ít nhất một mảng con liên tục có độ dài đúng bằng `k` và có tổng chia hết cho `m`.
- Không tồn tại bất kỳ mảng con liên tục nào có độ dài nhỏ hơn `k` (từ `1` đến `k - 1`) có tổng chia hết cho `m`.

Mục tiêu: In ra một mảng thỏa mãn điều kiện hoặc thông báo không thể xây dựng.

---

## 2. Phân tích tư duy và điều kiện bất khả thi (Key Insights)

Trước khi xây dựng mảng, cần xác định điều kiện nào khiến bài toán không có lời giải.

### Trường hợp 1: `k > m`

**Kết luận: NO**

Vì tất cả phần tử trong mảng đều là số nguyên dương nên mỗi phần tử nhỏ nhất bằng `1`.

Xét bất kỳ `m` phần tử liên tiếp nào:

- Tổng nhỏ nhất có thể là `m × 1 = m`.
- Độ dài của đoạn này là `m`.
- Vì `k > m`, ta có `m < k`.

Như vậy, luôn tồn tại một mảng con có độ dài nhỏ hơn `k` và tổng chia hết cho `m`.

Điều này vi phạm yêu cầu đề bài.

Do đó:

**Nếu `k > m` thì không thể xây dựng mảng hợp lệ.**

### Trường hợp 2: `k ≤ m`

**Kết luận: YES**

Ta có thể xây dựng một mảng thỏa mãn bằng cách sử dụng một khối mẫu có độ dài `k`, sau đó lặp lại khối này.

| Điều kiện | Kết quả | Giải thích |
|---|---|---|
| `k > m` | NO | Luôn tồn tại đoạn dài `m < k` có tổng chia hết cho `m`. |
| `k ≤ m` | YES | Có thể xây dựng mảng bằng khối mẫu. |

---

## 3. Chiến lược xây dựng mảng (Constructive Strategy)

Khi `k ≤ m`, ta sử dụng kỹ thuật **xây dựng khối mẫu (Pattern Building)**.

### 3.1. Xây dựng khối mẫu

Tạo một khối có độ dài đúng bằng `k`, gồm hai phần:

- `k - 1` phần tử đầu tiên: Gán bằng `1`.
- Phần tử thứ `k`: Gán giá trị bằng `m - k + 1`.

**Công thức khối mẫu:**

$$
Block = [1, 1, ..., 1, m-k+1]
$$

Trong đó có đúng `k - 1` phần tử bằng `1`.

**Ví dụ:** Với `k = 3`, `m = 5`:

$$
Block = [1, 1, 3]
$$

Tổng của khối:

$$
1+1+3=5=m
$$

Sau đó lặp lại khối mẫu cho đến khi đủ `n` phần tử.

### 3.2. Chứng minh tính đúng đắn (Correctness Proof)

Cần chứng minh hai điều kiện của đề bài đều được thỏa mãn.

**Điều kiện 1: Mọi mảng con độ dài `k` có tổng chia hết cho `m`.**

Trong dãy được xây dựng, các phần tử lặp lại theo chu kỳ:

```text
[1, 1, ..., 1, m-k+1]
```

Mọi đoạn liên tục có độ dài `k` đều chứa:

- `k - 1` phần tử bằng `1`.
- Một phần tử bằng `m - k + 1`.

Tổng của đoạn:

$$
\begin{aligned}
S &= (k-1)\times 1 + m-k+1\\
&=m
\end{aligned}
$$

Vì tổng bằng `m` nên chắc chắn chia hết cho `m`.

**Điều kiện 2: Không tồn tại mảng con độ dài nhỏ hơn `k` có tổng chia hết cho `m`.**

Xét hai trường hợp:

*Trường hợp A: Mảng con chỉ chứa các số `1`.*

Vì độ dài nhỏ hơn `k`, tổng lớn nhất là:

$$
S \leq k-1 < m
$$

Do đó, tổng không thể chia hết cho `m`.

*Trường hợp B: Mảng con chứa phần tử đặc biệt `m - k + 1`.*

Vì độ dài nhỏ hơn `k`, số lượng số `1` đi kèm tối đa chỉ là `k - 2`.

Tổng lớn nhất:

$$
\begin{aligned}
S &\leq m-k+1+(k-2)\\
&=m-1
\end{aligned}
$$

Vì:

$$
0 < S < m
$$

Nên tổng cũng không thể chia hết cho `m`.

**Kết luận:** Cả hai điều kiện đều được thỏa mãn. Thuật toán xây dựng mảng là hợp lệ.

---

## 4. Bài học rút ra (Key Takeaways)

Bài toán mang lại 4 bài học quan trọng khi giải các bài Constructive Algorithms ở mức Rating 900–1100.

### 1. Tìm điều kiện bất khả thi (Impossibility Boundary)

Trước khi tìm cách xây dựng mảng, hãy kiểm tra xem có điều kiện toán học nào khiến bài toán không có lời giải hay không.

Ở bài này:

$$
k > m \Rightarrow NO
$$

Điều này giúp loại bỏ trường hợp không thể giải quyết ngay từ đầu.

### 2. Kỹ thuật lặp khối mẫu (Block Pattern Repetition)

Đối với bài toán Constructive có tính chất tuần hoàn, hãy thử:

1. Tìm một khối mẫu nhỏ.
2. Chứng minh khối mẫu thỏa mãn yêu cầu.
3. Lặp lại khối mẫu để tạo ra mảng có độ dài `n`.

### 3. Kiểm tra bằng các trường hợp nhỏ (Small Case Testing)

Khi chưa tìm ra công thức, hãy thử một số giá trị nhỏ để quan sát quy luật.

Ví dụ:

- `k = 3, m = 5` → `[1, 1, 3]`
- `k = 4, m = 6` → `[1, 1, 1, 3]`

Việc thử nghiệm giúp kiểm tra giả thuyết trước khi viết code.

### 4. Kiểm tra ràng buộc miền giá trị (Constraint Verification)

Đề bài yêu cầu:

$$
a_i > 0
$$

Vì vậy, cần đảm bảo phần tử đặc biệt luôn dương:

$$
m-k+1 > 0
$$

Điều này tương đương:

$$
m \geq k
$$

Đây cũng chính là điều kiện để xây dựng mảng thành công.

---

## 5. Tổng kết tư duy giải bài

Có thể ghi nhớ toàn bộ hướng giải bằng quy trình sau:

1. Kiểm tra `k > m` → In `NO`.
2. Nếu `k ≤ m` → In `YES`.
3. Xây dựng khối mẫu gồm `k - 1` số `1` và một số `m - k + 1`.
4. Lặp lại khối mẫu cho đến khi đủ `n` phần tử.

**Ý tưởng cốt lõi:** Sử dụng các số `1` để giữ tổng của mọi đoạn ngắn hơn `k` nhỏ hơn `m`, đồng thời điều chỉnh phần tử cuối của khối để tổng của đoạn dài `k` bằng chính xác `m`.
