# quant-ranking-engine
A C++ implementation of a quantitative finance system that ranks stocks by combining multiple alpha factors (Momentum, Volatility, Volume Spike) using a custom-built merge sort algorithm. This project mimics the signal aggregation process used in hedge funds and algorithmic trading.

## 🚀 Features

- **Factor Calculation:** Computes momentum, volatility, and volume z-scores for a universe of stocks.
- **Cross-sectional Normalization:** Applies Z-score normalization to make factors comparable.
- **Custom Weighted Aggregation:** Combines factors into a single composite score using configurable weights (e.g., Momentum: 50%, Volatility: 30%, Volume: 20%).
- **Efficient Sorting:** Implements an in-place merge sort algorithm from scratch, optimized to sort by the composite score in **descending order**.
- **Portfolio Recommendations:** Outputs a ranked list of stocks with "Strong Buy" and "Strong Sell" suggestions.

## 🛠️ Tech Stack

- **Language:** C++11
- **Key Concepts:** Object-Oriented Programming (OOP), Custom Comparators, Pointer-based Sorting, Algorithm Analysis (O(n log n)), Financial Data Modeling

Through this project, I deepened my understanding of:
- Implementing core sorting algorithms (Merge Sort) and modifying them for specific use cases.
- Applying object-oriented principles to model real-world financial data.
- The quantitative finance workflow: factor calculation, normalization, aggregation, and ranking.
- Writing efficient C++ code using pointers and memory management.
