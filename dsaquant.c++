#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <deque>
using namespace std;

// 1. Stock class with enhanced data for pairs trading
class Stock {
public:
    string ticker;
    double currentPrice;
    vector<double> priceHistory;
    vector<double> returns;
    double volatility;

    Stock(string t, double initialPrice) : ticker(t), currentPrice(initialPrice) {
        priceHistory.push_back(initialPrice);
    }

    void addPriceUpdate(double newPrice) {
        // Calculate daily return
        double dailyReturn = (newPrice - currentPrice) / currentPrice;
        returns.push_back(dailyReturn);
        currentPrice = newPrice;
        priceHistory.push_back(newPrice);
    }

    void print() const {
        cout << left << setw(8) << ticker 
             << "Price: " << setw(10) << currentPrice
             << "Volatility: " << setw(10) << volatility
             << "Returns: " << returns.size() << " days" << endl;
    }
};

// 2. SLIDING WINDOW: Calculate rolling volatility efficiently
double calculateRollingVolatility(const vector<double>& returns, int windowSize) {
    if (returns.size() < windowSize) return 0.0;

    double sum = 0.0;
    double sqSum = 0.0;

    // Calculate initial window
    for (int i = 0; i < windowSize; i++) {
        sum += returns[i];
        sqSum += returns[i] * returns[i];
    }

    double mean = sum / windowSize;
    double variance = (sqSum / windowSize) - (mean * mean);
    return sqrt(max(variance, 0.0)); // Ensure non-negative
}

// 3. BINARY SEARCH: Order Book management for limit orders
class OrderBook {
private:
    vector<pair<double, int>> bids; // price, quantity (descending)
    vector<pair<double, int>> asks; // price, quantity (ascending)

public:
    void addBid(double price, int quantity) {
        // Find insertion point using binary search
        int left = 0, right = bids.size(), pos = bids.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (bids[mid].first > price) {
                left = mid + 1;
            } else {
                pos = mid;
                right = mid;
            }
        }
        bids.insert(bids.begin() + pos, {price, quantity});
    }

    void printTop() const {
        cout << "Top Bid: " << (bids.empty() ? 0 : bids[0].first) 
             << ", Top Ask: " << (asks.empty() ? 0 : asks[0].first) << endl;
    }
};

// 4. TWO POINTERS: Find best pairs trading opportunity
void findBestTradingWindow(const vector<double>& spread, int& entry, int& exit) {
    double maxProfit = 0;
    double currentProfit = 0;
    int currentStart = 0;
    entry = exit = 0;

    for (int i = 0; i < spread.size(); i++) {
        currentProfit += spread[i];
        
        if (currentProfit < 0) {
            currentProfit = 0;
            currentStart = i + 1;
        }
        
        if (currentProfit > maxProfit) {
            maxProfit = currentProfit;
            entry = currentStart;
            exit = i;
        }
    }
}

// 5. Main analysis function
void analyzePairs(Stock& stock1, Stock& stock2, int windowSize) {
    if (stock1.returns.size() != stock2.returns.size()) {
        cout << "Error: Price history mismatch!" << endl;
        return;
    }

    // Calculate spread between two stocks
    vector<double> spread;
    for (int i = 0; i < stock1.returns.size(); i++) {
        spread.push_back(stock1.returns[i] - stock2.returns[i]);
    }

    // Use Two Pointers to find best trading window
    int entryDay, exitDay;
    findBestTradingWindow(spread, entryDay, exitDay);
    
    double entryPrice1 = stock1.priceHistory[entryDay];
    double entryPrice2 = stock2.priceHistory[entryDay];
    double exitPrice1 = stock1.priceHistory[exitDay];
    double exitPrice2 = stock2.priceHistory[exitDay];

    // Calculate potential profit from pairs trade
    double profit = (exitPrice2 - entryPrice2) - (exitPrice1 - entryPrice1);

    cout << "\n=== PAIRS TRADING ANALYSIS ===" << endl;
    cout << "Stocks: " << stock1.ticker << " vs " << stock2.ticker << endl;
    cout << "Optimal trade window: Day " << entryDay << " to Day " << exitDay << endl;
    cout << "Strategy: Buy " << stock2.ticker << " (@ " << entryPrice2 
         << "), Short " << stock1.ticker << " (@ " << entryPrice1 << ")" << endl;
    cout << "Exit: Sell " << stock2.ticker << " (@ " << exitPrice2 
         << "), Cover " << stock1.ticker << " (@ " << exitPrice1 << ")" << endl;
    cout << "Potential Profit: " << profit << endl;
    cout << "Annualized Return: " << (profit / abs(entryPrice1 + entryPrice2)) * 252 << "%" << endl;
}

int main() {
    cout << "=== QUANTITATIVE TRADING ANALYSIS PLATFORM ===" << endl;
    cout << "Implementing Sliding Window, Binary Search, and Two Pointers\n" << endl;

    // Create sample stocks with price history
    Stock infy("INFY", 1500.0);
    Stock tcs("TCS", 3800.0);

    // Simulate 100 days of price data with correlation
    for (int day = 1; day <= 100; day++) {
        double infyChange = (rand() % 100 - 50) / 100.0; // -0.5% to +0.5%
        double tcsChange = infyChange + (rand() % 40 - 20) / 100.0; // Correlated but not perfect
        
        infy.addPriceUpdate(infy.currentPrice * (1 + infyChange/100));
        tcs.addPriceUpdate(tcs.currentPrice * (1 + tcsChange/100));
    }

    // 1. Calculate volatility using SLIDING WINDOW
    const int volatilityWindow = 20;
    infy.volatility = calculateRollingVolatility(infy.returns, volatilityWindow);
    tcs.volatility = calculateRollingVolatility(tcs.returns, volatilityWindow);

    cout << "--- VOLATILITY ANALYSIS (Sliding Window) ---" << endl;
    infy.print();
    tcs.print();

    // 2. Demonstrate ORDER BOOK with BINARY SEARCH
    OrderBook niftyOrderBook;
    niftyOrderBook.addBid(18000.50, 100);
    niftyOrderBook.addBid(18000.25, 150);
    niftyOrderBook.addBid(18001.00, 75); // Should be inserted at correct position
    
    cout << "\n--- ORDER BOOK SIMULATION (Binary Search) ---" << endl;
    niftyOrderBook.printTop();

    // 3. PAIRS TRADING with TWO POINTERS
    analyzePairs(infy, tcs, 30);

    // 4. Risk Management: Portfolio optimization
    cout << "\n--- RISK ANALYSIS ---" << endl;
    double portfolioVolatility = sqrt(infy.volatility*infy.volatility + 
                                    tcs.volatility*tcs.volatility);
    cout << "Estimated Portfolio Volatility: " << portfolioVolatility * 100 << "%" << endl;
    
    // Calculate optimal position sizing (inverse volatility weighting)
    double infyWeight = (1/infy.volatility) / (1/infy.volatility + 1/tcs.volatility);
    double tcsWeight = 1 - infyWeight;
    
    cout << "Optimal Weights: " << infy.ticker << ": " << infyWeight * 100 
         << "%, " << tcs.ticker << ": " << tcsWeight * 100 << "%" << endl;

    return 0;
}