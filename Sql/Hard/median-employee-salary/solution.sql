WITH number_stats AS (
    SELECT
        num,
        frequency,

        SUM(frequency) OVER (
            ORDER BY num
            ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
        ) AS cum_freq,

        SUM(frequency) OVER () AS total_freq

    FROM Numbers
),

median_positions AS (
    SELECT
        num,
        frequency,
        cum_freq,
        total_freq,

        CASE
            WHEN total_freq % 2 = 0
                THEN total_freq / 2
            ELSE (total_freq + 1) / 2
        END AS left_pos,

        CASE
            WHEN total_freq % 2 = 0
                THEN total_freq / 2 + 1
            ELSE (total_freq + 1) / 2
        END AS right_pos

    FROM number_stats
)

SELECT num
FROM median_positions
WHERE cum_freq >= left_pos
  AND cum_freq - frequency < right_pos;
