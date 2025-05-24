import os

import pandas as pd
from pandas.core.interchange.dataframe_protocol import DataFrame

from constants import Constants
from errors_module import ExceptionDescription, print_error_region, BigDataError
from logic_module import validate_region

def read_csv_file(filepath_entered):
    data = None
    try:
        file_size = os.path.getsize(filepath_entered)
        if file_size > Constants.max_size_bytes:
            raise BigDataError
        data = pd.read_csv(filepath_entered, header = None)
        data.columns = ['year','region','npg','birth_rate','death_rate','gdw','urbanization']
    except FileNotFoundError:
        print(ExceptionDescription.file_not_found)
    except pd.errors.EmptyDataError:
        print(ExceptionDescription.empty_data)
    except pd.errors.ParserError:
        print(ExceptionDescription.parser_error)
    except BigDataError:
        print(ExceptionDescription.big_file)
    finally:
        return data

def read_region(data: DataFrame):
    result = None
    region = input("\nEnter your region: ")
    if validate_region(data, region):
        result = region
    return result


def read_column(region):
    column = None
    if region is not None:
        print("Text one of them:\n\n"
              "year\n"
              "npg\n"
              "birth_rate\n"
              "death_rate\n"
              "gdw\n"
              "urbanization\n")
        column = input("Enter column for analysis: ")
    else:
        print_error_region()
    return column