# AlgoTrading - Algorithmic Order Execution Trading Module

## Feature Overview

AlgoTrading is a module for **algorithmic order execution trading**. Users can operate through its UI interface to easily complete tasks such as starting algorithms, saving configurations, and stopping algorithms.

Algorithmic trading handles the specific execution process of order delegation. Currently, AlgoTrading offers a variety of example algorithms, enabling users to automatically split large orders into suitable smaller batch orders, effectively reducing trading costs and impact costs (such as iceberg and sniper algorithms), as well as engage in high sell low buy operations within a set threshold (such as grid and arbitrage algorithms).

## Loading and Startup

### Loading through VeighNa Station

After logging into the VeighNa Station, click on the "Trading" button, and select “AlgoTrading” in the application module section of the configuration dialog box.

### Script Loading

Add the following code to the startup script:

```python
# At the beginning
from vnpy_algotrading import AlgoTradingApp

# After creating the main_engine object
main_engine.add_app(AlgoTradingApp)
```

## Module Startup

For algorithms set up by users, they need to be placed in the `algo_trading.algos` directory to be recognized and loaded.

Before initiating the module, please first connect to the trading interface (for connection methods, refer to the connection interface section in the basic usage guide). Start the module only after seeing the “Contract information query succeeded” message displayed in the log section of the VeighNa Trader main interface, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

Please note that the IB interface cannot automatically retrieve all contract information at login; it can only do so when the user manually subscribes to the market data. Therefore, it is necessary to manually subscribe to the contract market data on the main interface before launching the module.

After successfully connecting to the trading interface, click on "Function" -> "Algorithmic Trading" in the menu bar, or click the icon in the left sidebar:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/1.png)

You will then be able to enter the UI interface of the Algorithmic Delegated Execution Trading module, as illustrated below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/10.png)

## Algorithm Configuration

The requirements for configuring parameters are as follows:

- Algorithm: Select the trading algorithm to be executed from the dropdown menu.
- Local Code: The format is `vt_symbol` (contract code + exchange name).
- Direction: Long or Short.
- Price: The price for placing an order.
- Quantity: The total quantity of the order, which needs to be broken down into smaller batch orders for trading.
- Execution Time (seconds): The total time for running the trading algorithm, measured in seconds.
- Round Interval (seconds): The time interval for placing orders, measured in seconds.
- Open/Close: Open, Close, Close Today, Close Yesterday.

### Save Configuration

The trading algorithm configuration information can be saved locally in a JSON file, so there is no need to re-enter it each time you open the algorithmic trading module. The specific operations are as follows:

- In the "Configuration Name" option, enter the name for this algorithm configuration information, and then click the "Save Configuration" button below to save the configuration information locally.
- After saving the configuration, you can see the saved configuration name and configuration parameters in the "Configuration" component on the right side of the interface.

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/4.png)

The saved configuration file can be found in the `.vntrader` folder under `algo_trading_setting.json`, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/5.png)

## Launching the Algorithm

Currently, VeighNa offers six commonly used sample algorithms. This document takes the Time-Weighted Average Price (TWAP) algorithm as an example to illustrate the process of launching the algorithm.

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/3.png)

Once the parameter configuration is complete (for saved algorithm information, you can switch the information content of the configuration on the left side of the interface by clicking "Use" under the corresponding algorithm in the "Configuration" column), click the "Launch Algorithm" button to immediately execute algorithmic trading.

If the launch is successful, you can observe the execution status of the algorithm in the "In Execution" interface in the upper right corner.

The specific task executed by the algorithm in the picture is as follows: Using the Time-Weighted Average Price (TWAP) algorithm, buying 10,000 lots of soybean oil 2109 contracts (y2109) at an execution price of 9000 yuan, with an execution time of 600 seconds and a round interval of 6 seconds. That is, every 6 seconds, when the first sell price of the contract is less than or equal to 9000, buy 100 lots of soybean oil 2109 contracts at a price of 9000, splitting the buying operation into 100 times.

## CSV Launch

When there are many algorithms that need to be launched, you can launch them in bulk at one time through a CSV file. Click the "CSV Launch" button on the left side of the graphic interface, and quickly launch the algorithm by opening the desired CSV file in the pop-up dialog box.

Please note, the format of the CSV file should be as shown in the picture below, consistent with the fields in the left editing area:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/12.png)

Using Excel's quick table editing feature makes it relatively convenient to add algorithms in bulk. After a successful launch, the execution status of all the algorithms in the CSV file will be displayed under the "In Execution" interface, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/14.png)

Please note that after the CSV launch, you can only observe the content output and changes in the "In Execution", "Log", and "Ended" three interfaces; the algorithm information in the CSV file will not be added to the configurations.

## Stopping the Algorithm

When the user needs to stop a trading algorithm that is currently executing, they can click the "Stop" button in the "In Execution" interface to stop a specific algorithm trade, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/6.png)

Users can also click the "Stop All" button at the bottom of the trade delegation interface to stop all executing algorithm trades at once, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/7.png)

## Data Monitoring

The data monitoring interface consists of four parts:

- **In Execution Component**: Displays the algorithm trades that are currently executing, including: the algorithm, parameters, and status. After successfully starting the algorithm, switch to the "In Execution" interface in the upper right corner to display the execution status of the algorithm, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/6.png)

- **Completed Component**: Displays the algorithmic trades that have been completed, including: the algorithm, parameters, and status. After the algorithm ends or is stopped, switch to the "Completed" interface in the upper right corner to display the execution status of the algorithm, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/9.png)

- **Log Component**: Displays related log information of starting, stopping, and completing the algorithm. After opening the algorithm trading module, initialization will be performed, hence the "Log" component will first output "Algorithm trading engine started" and "Algorithm configuration loaded successfully", as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/11.png)

- **Configuration Component**: Used to load the configuration information from `algo_trading_setting.json` and display it graphically under the "Configuration" column, as shown in the picture below:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/algo_trading/8.png)

- Click the **Use** button in the configuration component to immediately read this configuration information and display it on the trading commission interface, then click **Start Algorithm** to start trading;
- Click the **Remove** button in the configuration component to remove this algorithm configuration, and synchronize updates to the JSON file.

## Sample Algorithms

The sample algorithm paths are located under the `algo_trading.algos` folder (please note, individual algorithms do not have open and flat directions written, if needed, personalized modifications can be made based on individual needs). Currently, the algorithmic trading module offers the following six built-in algorithms:

### DMA - Direct Market Access Algorithm

The Direct Market Access (DMA) Algorithm directly issues new orders (limit orders, stop orders, market orders).

### TWAP - Time-Weighted Average Price Algorithm

The Time-Weighted Average Price (TWAP) Algorithm executes as follows:

- Distribute the order quantity evenly over a certain time period, hanging a buy (or sell) order at the specified price at regular intervals.
- **Buying scenario**: When the ask price is lower than the target price, issue an order; the order quantity takes the minimum value between the remaining order quantity and the order split quantity.
- **Selling scenario**: When the bid price is higher than the target price, issue an order; the order quantity takes the minimum value between the remaining order quantity and the order split quantity.

### Iceberg - Iceberg Algorithm

The Iceberg Algorithm executes as follows:

- Place an order at a certain price, but only place a part of it until all are traded.

- **Buying scenario**: Check the cancellation first; if the latest Tick ask price is lower than the target price, execute the cancellation; if there is no active order, issue an order, the order quantity takes the minimum value between the remaining order quantity and the displayed order quantity.

- **Selling scenario**: Check the cancellation first; if the latest Tick bid price is higher than the target price, execute the cancellation; if there is no active order, issue an order, the order quantity takes the minimum value between the remaining order quantity and the displayed order quantity.

### Sniper - Sniper Algorithm

The Sniper Algorithm executes as follows:

- Monitor the latest Tick push quotes, and immediately quote a good price to trade.

- **Buying scenario**: When the latest Tick ask price is lower than the target price, issue an order; the order quantity takes the minimum value between the remaining order quantity and the ask quantity.

- **Selling scenario**: When the latest Tick bid price is higher than the target price, issue an order; the order quantity takes the minimum value between the remaining order quantity and the bid quantity.

### Stop - Conditional Order Algorithm

The Conditional Order (Stop) Algorithm executes as follows:

- Monitor the latest Tick push quotes, and immediately quote to trade when a market breakthrough is found.

- **Buying scenario**: When the Tick latest price is higher than the target price, issue an order; the order price is the target price plus the premium.

- **Selling scenario**: When the Tick latest price is lower than the target price, issue an order; the order price is the target price minus the premium.

### BestLimit - Best Limit Price Algorithm

The Best Limit Price (BestLimit) Algorithm executes as follows:

- Monitor the latest Tick push quotes, and immediately quote a good price to trade.

- **Buying scenario**: First check the cancellation: when the latest Tick bid price is not equal to the target price, execute the cancellation; if there is no active order, issue an order, the order price is the latest Tick bid price, and the order quantity is the remaining order quantity.

- **Selling scenario**: First check the cancellation: when the latest Tick bid price is not equal to the target price, execute the cancellation; if there is no active order, issue an order, the order price is the latest Tick ask price, and the order quantity is the remaining order quantity.
