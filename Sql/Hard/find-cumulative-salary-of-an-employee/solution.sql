SELECT id, month, Salary
FROM (
    SELECT 
        id, 
        month,
        SUM(salary) OVER (
            PARTITION BY id 
            ORDER BY month 
            RANGE BETWEEN 2 PRECEDING AND CURRENT ROW
        ) AS Salary,
        MAX(month) OVER (PARTITION BY id) AS max_month
    FROM Employee
) t
WHERE month != max_month
ORDER BY id ASC, month DESC;