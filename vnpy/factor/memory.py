import polars as pl
from pathlib import Path
from typing import Optional, Dict, Union, Tuple, List
import shutil  # For atomic write (rename)
from threading import Lock # For thread safety
import os # For os.getpid()

class FactorMemory:
    """
    Manages factor historical data using memory-mapped Arrow IPC files,
    acting as a fixed-size circular buffer.

    This class ensures thread-safe operations and atomic writes to protect data integrity.
    It strictly enforces a schema for the stored data.

    Attributes:
        file_path (Path): Path to the Arrow IPC file.
        max_rows (int): Maximum number of rows to store (capacity of the circular buffer).
        schema (Dict[str, pl.PolarsDataType]): Schema of the DataFrame.
        datetime_col (str): Name of the datetime column, used for sorting and de-duplication.
        _lock (Lock): Thread lock for ensuring safe concurrent file access.
    """

    def __init__(
        self,
        file_path: Union[str, Path],
        max_rows: int,
        schema: Dict[str, pl.DataType],
        datetime_col: str = "datetime"
    ):
        """
        Initializes the FactorMemory instance.

        Args:
            file_path: Path to the Arrow IPC file where data will be stored.
            max_rows: Maximum number of rows to maintain in the circular buffer.
                      Must be greater than 0.
            schema: A dictionary defining column names and their Polars data types.
                    Example: {"datetime": pl.Datetime(time_unit="us"), "value": pl.Float64}
            datetime_col: The name of the column that serves as the primary time index.
                          This column must be part of the schema and have a datetime or date type.
        
        Raises:
            ValueError: If max_rows is not positive, schema is empty, or datetime_col
                        is misconfigured or missing from the schema.
            IOError: If the factor memory file cannot be initialized.
        """
        if max_rows <= 0:
            raise ValueError("max_rows must be a positive integer.")
        if not schema:
            raise ValueError("Schema cannot be empty.")
        if datetime_col not in schema:
            raise ValueError(f"datetime_col '{datetime_col}' must be defined in the schema.")

        self.file_path = Path(file_path).resolve() # Use absolute path
        self.max_rows = max_rows
        self.schema = schema
        self.datetime_col = datetime_col
        self._lock = Lock()

        self.file_path.parent.mkdir(parents=True, exist_ok=True)
        self._initialize_if_empty()

    def _initialize_if_empty(self) -> None:
        with self._lock:
            try:
                should_initialize = True
                if self.file_path.exists() and self.file_path.stat().st_size > 0:
                    try:
                        existing_df = pl.read_ipc(self.file_path, memory_map=False, use_pyarrow=True)
                        # Check if schemas are equivalent, not necessarily identical objects
                        if existing_df.schema == self.schema: # Polars schema comparison
                            should_initialize = False
                        else:
                            print(f"Warning: File {self.file_path} exists with mismatched schema. "
                                  f"Expected: {self.schema}, Found: {existing_df.schema}. Re-initializing.")
                    except Exception as e:
                        print(f"Warning: Could not read existing file {self.file_path} (Reason: {e}). Re-initializing.")
                
                if should_initialize:
                    empty_df = pl.DataFrame(data={}, schema=self.schema)
                    empty_df.write_ipc(self.file_path, compression="lz4") 
                    print(f"Initialized factor memory file: {self.file_path} with schema: {self.schema}")
            except Exception as e_init:
                raise IOError(f"Failed to initialize factor memory file {self.file_path}: {e_init}") from e_init

    def _conform_df_to_schema(self, df: pl.DataFrame, df_name: str = "input") -> pl.DataFrame:
        """
        Conforms an input DataFrame to the FactorMemory instance's schema.

        It ensures all columns from `self.schema` exist, are in the correct order,
        and attempts to cast data types if they don't match. Missing columns
        are filled with nulls. Issues are collected and printed as warnings.

        Args:
            df: The input DataFrame to conform.
            df_name: A descriptive name for the input DataFrame, used in warning messages.

        Returns:
            A new DataFrame that strictly adheres to `self.schema`.
        """
        if df.schema == self.schema:
            return df

        conformed_cols = {}
        errors = []
        
        # Create a mapping of existing column names to their current dtypes for quick lookup
        current_df_schema = df.schema

        for col_name, expected_dtype in self.schema.items():
            if col_name in current_df_schema:
                current_dtype = current_df_schema[col_name]
                if current_dtype == expected_dtype:
                    conformed_cols[col_name] = df.get_column(col_name)
                else:
                    try:
                        conformed_cols[col_name] = df.get_column(col_name).cast(expected_dtype, strict=False)
                    except Exception as e: 
                        errors.append(f"Could not cast column '{col_name}' in {df_name} DataFrame from {current_dtype} to {expected_dtype}: {e}")
                        conformed_cols[col_name] = pl.Series([None] * len(df), dtype=expected_dtype, name=col_name)
            else:
                errors.append(f"Column '{col_name}' missing in {df_name} DataFrame. Adding as nulls with type {expected_dtype}.")
                conformed_cols[col_name] = pl.Series([None] * len(df), dtype=expected_dtype, name=col_name)
        
        if errors:
            print(f"Warning: Schema conformance issues for {self.file_path} with {df_name} DataFrame:\n" + "\n".join(errors))
        
        # Ensure correct column order as defined in self.schema
        return pl.DataFrame(conformed_cols).select(list(self.schema.keys()))


    def _load_data(self) -> pl.DataFrame:
        if not self.file_path.exists() or self.file_path.stat().st_size == 0:
            return pl.DataFrame(data={}, schema=self.schema)
        try:
            # It's generally safer to read without memory_map if the file might be modified externally
            # or if schema conformance is complex. For internal use where this class controls writes,
            # memory_map=True is fine for reads.
            df = pl.read_ipc(self.file_path, memory_map=True, use_pyarrow=True) 
            return self._conform_df_to_schema(df, "loaded")
        except Exception as e:
            print(f"Error loading data from {self.file_path}: {e}. Returning empty DataFrame with schema.")
            return pl.DataFrame(data={}, schema=self.schema)

    def _save_data(self, df: pl.DataFrame) -> None:
        df_to_save = self._conform_df_to_schema(df, "data_to_save")
        temp_file_path = self.file_path.with_suffix(f"{self.file_path.suffix}.{os.getpid()}.tmp")
        try:
            df_to_save.write_ipc(temp_file_path, compression="lz4")
            shutil.move(str(temp_file_path), str(self.file_path))
        except Exception as e:
            # Clean up temp file if it exists after a failed save or move
            if temp_file_path.exists():
                try:
                    temp_file_path.unlink(missing_ok=True) # missing_ok for Python 3.8+
                except OSError:
                     if temp_file_path.exists(): # check again for race condition
                        os.remove(temp_file_path)

            raise IOError(f"Failed to save data to {self.file_path}: {e}") from e
        finally:
             if temp_file_path.exists(): # Final cleanup check
                try:
                    temp_file_path.unlink(missing_ok=True)
                except OSError:
                    if temp_file_path.exists():
                        os.remove(temp_file_path)


    def get_data(self) -> pl.DataFrame:
        with self._lock:
            return self._load_data()

    def update_data(self, new_data: pl.DataFrame) -> None:
        if new_data is None or new_data.is_empty():
            # print(f"Debug: update_data called with empty or None new_data for {self.file_path}. No action taken.")
            return

        with self._lock:
            try:
                conformed_new_data = self._conform_df_to_schema(new_data, "new_data_input")
            except Exception as e:
                raise ValueError(f"Fatal schema error in new_data for {self.file_path}: {e}") from e

            current_data = self._load_data()
            
            if current_data.is_empty():
                combined_data = conformed_new_data
            else:
                combined_data = pl.concat([current_data, conformed_new_data], how="vertical_relaxed")
            
            if self.datetime_col not in combined_data.columns:
                 # This case should ideally be prevented by _conform_df_to_schema
                raise ValueError(f"Internal error: Datetime column '{self.datetime_col}' not found "
                                 f"in combined data for {self.file_path}. Schema: {combined_data.schema}")

            # Sort by datetime, remove duplicates (preferring last entries for ties),
            # and then sort again to ensure final order.
            # Ensure datetime_col is actually sortable (e.g., not all nulls if it's critical)
            if combined_data.get_column(self.datetime_col).null_count() == len(combined_data):
                print(f"Warning: Datetime column '{self.datetime_col}' in {self.file_path} is all nulls. "
                      "Cannot sort or de-duplicate effectively by datetime.")
                # If all datetime are null, unique won't work as expected on it.
                # We might need a different strategy or just take the tail.
                # For now, proceed, but this is a data quality flag.
            else:
                 combined_data = combined_data.sort(by=self.datetime_col).unique(
                    subset=[self.datetime_col], keep="last", maintain_order=False
                ).sort(by=self.datetime_col) 
            
            if len(combined_data) > self.max_rows:
                combined_data = combined_data.tail(self.max_rows)
            
            self._save_data(combined_data)

    def get_shape(self) -> Tuple[int, int]:
        with self._lock:
            if not self.file_path.exists() or self.file_path.stat().st_size == 0:
                return (0, len(self.schema))
            df = self._load_data()
            return df.shape

    def get_latest_rows(self, n: int) -> pl.DataFrame:
        if n <= 0:
            return pl.DataFrame(data={}, schema=self.schema)
        with self._lock:
            df = self._load_data()
            if df.is_empty():
                return df
            return df.tail(n)

    def get_oldest_rows(self, n: int) -> pl.DataFrame:
        if n <= 0:
            return pl.DataFrame(data={}, schema=self.schema)
        with self._lock:
            df = self._load_data()
            if df.is_empty():
                return df
            return df.head(n)

    def clear(self) -> None:
        with self._lock:
            empty_df = pl.DataFrame(data={}, schema=self.schema)
            self._save_data(empty_df)
        print(f"Factor memory file cleared and re-initialized: {self.file_path}")

    @property
    def is_empty(self) -> bool:
        return self.get_shape()[0] == 0

    def __repr__(self) -> str:
        return (f"FactorMemory(file_path='{self.file_path}', max_rows={self.max_rows}, "
                f"schema_cols={list(self.schema.keys())}, datetime_col='{self.datetime_col}')")

