# encoding: utf-8
import os
import zipfile
from datetime import timedelta
from multiprocessing import Pool

import polars as pl
import requests
from tqdm import tqdm


class BinanceKlineDownloader:
    # Binance Spot
    BASE_URL = 'https://data.binance.vision/data/spot/daily/klines'
    columns = ["open_time", "open", "high", "low", "close", "volume", "close_time",
               "quote_asset_volume", "number_of_trades", "taker_buy_base_asset_volume",
               "taker_buy_quote_asset_volume", "ignore"]

    # ['open_time','open','high','low','close','volume','close_time','quote_volume','count','taker_buy_volume','taker_buy_quote_volume','ignore']

    def __init__(self, symbol, interval, start_date, end_date, save_dir):
        self.symbol = symbol.upper()
        self.interval = interval
        self.start_date = start_date
        self.end_date = end_date
        self.save_dir = os.path.join(save_dir, interval, symbol)

        # Ensure the save directory exists
        if not os.path.exists(self.save_dir):
            os.makedirs(self.save_dir)

    def download_klines(self, date):
        year, month, day = date.year, date.month, date.day

        filename = f"{self.symbol}-{self.interval}-{year}-{str(month).zfill(2)}-{str(day).zfill(2)}.zip"
        csv_filename = filename.replace('.zip', '.csv')
        filepath = os.path.join(self.save_dir, filename)
        csv_filepath = os.path.join(self.save_dir, csv_filename)

        if os.path.exists(csv_filepath):
            # print(f"Data for {self.symbol} on {year}-{month}-{day} already exists. Skipping...")
            return csv_filepath

        url = f"{self.BASE_URL}/{self.symbol.upper()}/{self.interval}/{filename}"

        try:
            response = requests.get(url, stream=True)
            response.raise_for_status()

            with open(filepath, 'wb') as f:
                for chunk in response.iter_content(chunk_size=8192):
                    f.write(chunk)

            with zipfile.ZipFile(filepath, 'r') as zip_ref:
                zip_ref.extractall(self.save_dir)

            # Check if CSV has headers
            # with open(csv_filepath, 'r') as f:
            #     first_line = f.readline().strip()
            #     has_header = not any(
            #         char.isdigit() for char in first_line)  # Check if there's any number in the first line

            df = pl.read_csv(csv_filepath, has_header=False, new_columns=self.columns)
            # df = df.with_columns(
            #     pl.from_epoch('open_time', time_unit='ms').dt.strftime('%Y-%m-%d %H:%M:%S'),
            #     pl.from_epoch('close_time', time_unit='ms').dt.strftime('%Y-%m-%d %H:%M:%S')
            # )
            # df=df.rename({'open_time':'datetime'})
            df.write_csv(csv_filepath)
            os.remove(filepath)

            return csv_filepath

        except requests.HTTPError as e:
            print(f'Failed to fetch files for {self.symbol} on {year}-{month}-{day}. HTTP error: {e}')
        except Exception as e:
            print(f"An error occurred while processing {self.symbol} on {year}-{month}-{day}. Error: {e}")

    def worker(self, date):
        return self.download_klines(date)

    def download(self, core):
        date_list = [self.start_date + timedelta(days=i) for i in range((self.end_date - self.start_date).days + 1)]

        # Apply the progress bar using tqdm
        with Pool(core) as p:
            for _ in tqdm(p.imap(self.worker, date_list), total=len(date_list)):
                pass


class BinanceTradesDownloader:
    BASE_URL = 'https://data.binance.vision/data/spot/daily/trades'
    columns = ["trade_id", "price", "qty", "quoteQty", "time", "isBuyerMaker"]

    def __init__(self, symbol, start_date, end_date, save_dir):
        self.symbol = symbol
        self.start_date = start_date
        self.end_date = end_date
        self.save_dir = os.path.join(save_dir, symbol)

        # Ensure the save directory exists
        if not os.path.exists(self.save_dir):
            os.makedirs(self.save_dir)

    def download_trades(self, date, n_tries=3):
        year, month, day = date.year, date.month, date.day

        filename = f"{self.symbol}-trades-{year}-{str(month).zfill(2)}-{str(day).zfill(2)}.zip"
        # filename=kline_filename_format.format(symbol=self.symbol, year=year, month=str(month).zfill(2), day=str(day).zfill(2)) # todo
        csv_filename = filename.replace('.zip', '.csv')
        filepath = os.path.join(self.save_dir, filename)
        csv_filepath = os.path.join(self.save_dir, csv_filename)

        if os.path.exists(csv_filepath):
            return csv_filepath

        url = f"{self.BASE_URL}/{self.symbol.upper()}/{filename}"

        for i in range(n_tries):

            try:
                response = requests.get(url, stream=True)
                response.raise_for_status()

                with open(filepath, 'wb') as f:
                    for chunk in response.iter_content(chunk_size=8192):
                        f.write(chunk)

                with zipfile.ZipFile(filepath, 'r') as zip_ref:
                    zip_ref.extractall(self.save_dir)

                # Check if CSV has headers
                # with open(csv_filepath, 'r') as f:
                #     first_line = f.readline().strip()
                #     has_header = not any(
                #         char.isdigit() for char in first_line)  # Check if there's any number in the first line

                df = pl.read_csv(csv_filepath, has_header=False, new_columns=self.columns)

                # df = df.with_columns(
                #     pl.from_epoch('time', time_unit='ms').dt.strftime('%Y-%m-%d %H:%M:%S')
                # )
                df.write_csv(csv_filepath)
                os.remove(filepath)

                return csv_filepath

            except requests.HTTPError as e:
                print(f'Failed to fetch files for {self.symbol} on {year}-{month}-{day}. HTTP error: {e}')
            except Exception as e:
                print(f"An error occurred while processing {self.symbol} on {year}-{month}-{day}. Error: {e}")

    def worker(self, date):
        return self.download_trades(date)

    def download(self, core):
        date_list = [self.start_date + timedelta(days=i) for i in range((self.end_date - self.start_date).days + 1)]

        with Pool(core) as p:
            for _ in tqdm(p.imap(self.worker, date_list), total=len(date_list)):
                pass

class BinanceAggTradesDownloader:
    """
    下载binance的逐笔数据
    doc : https://binance-docs.github.io/apidocs/spot/en/#old-trade-lookup:~:text=Data%20Source%3A%20Database-,Compressed/Aggregate%20Trades%20List,-Response%3A
    """
    BASE_URL = 'https://data.binance.vision/data/spot/daily/aggTrades'
    sample = {
        "a": 26129,  # Aggregate tradeId
        "p": "0.01633102",  # Price
        "q": "4.70443515",  # Quantity
        "f": 27781,  # First tradeId
        "l": 27781,  # Last tradeId
        "T": 1498793709153,  # Timestamp in unix
        "m": True,  # Was the buyer the maker?
        "M": True  # Was the trade the best price match?
    }
    query_cols =list(sample.keys())
    columns = ["agg_trade_id", "price", "qty", "f_trade_id", "l_trade_id", "timestamp", "is_buyer_maker", "is_best_price"]

    def __init__(self, symbol, start_date, end_date, save_dir):
        self.symbol = symbol
        self.start_date = start_date
        self.end_date = end_date
        self.save_dir = os.path.join(save_dir, symbol)

        # Ensure the save directory exists
        if not os.path.exists(self.save_dir):
            os.makedirs(self.save_dir)

    def download_trades(self, date, n_tries=3):
        year, month, day = date.year, date.month, date.day

        filename = f"{self.symbol}-aggTrades-{year}-{str(month).zfill(2)}-{str(day).zfill(2)}.zip"
        # filename=kline_filename_format.format(symbol=self.symbol, year=year, month=str(month).zfill(2), day=str(day).zfill(2)) # todo
        csv_filename = filename.replace('.zip', '.csv')
        filepath = os.path.join(self.save_dir, filename)
        csv_filepath = os.path.join(self.save_dir, csv_filename)

        if os.path.exists(csv_filepath):
            return csv_filepath

        url = f"{self.BASE_URL}/{self.symbol.upper()}/{filename}"

        for i in range(n_tries):

            try:
                response = requests.get(url, stream=True)
                response.raise_for_status()

                with open(filepath, 'wb') as f:
                    for chunk in response.iter_content(chunk_size=8192):
                        f.write(chunk)

                with zipfile.ZipFile(filepath, 'r') as zip_ref:
                    zip_ref.extractall(self.save_dir)

                # Check if CSV has headers
                # with open(csv_filepath, 'r') as f:
                #     first_line = f.readline().strip()
                #     has_header = not any(
                #         char.isdigit() for char in first_line)  # Check if there's any number in the first line

                df = pl.read_csv(csv_filepath, has_header=False, new_columns=self.columns)

                # df = df.with_columns(
                #     pl.from_epoch('time', time_unit='ms').dt.strftime('%Y-%m-%d %H:%M:%S')
                # )
                df.write_csv(csv_filepath)
                os.remove(filepath)

                return csv_filepath

            except requests.HTTPError as e:
                print(f'Failed to fetch files for {self.symbol} on {year}-{month}-{day}. HTTP error: {e}')
            except Exception as e:
                print(f"An error occurred while processing {self.symbol} on {year}-{month}-{day}. Error: {e}")

    def worker(self, date):
        return self.download_trades(date)

    def download(self, core):
        date_list = [self.start_date + timedelta(days=i) for i in range((self.end_date - self.start_date).days + 1)]

        with Pool(core) as p:
            for _ in tqdm(p.imap(self.worker, date_list), total=len(date_list)):
                pass