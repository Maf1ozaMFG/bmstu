from idlelib.iomenu import errors

import numpy as np
import pandas as pd
from pandas import DataFrame


def calculate_stats(data_sorted_region, column):
    result = None
    try:
        data = data_sorted_region[column]
        data_numeric = pd.to_numeric(data, errors='coerce')
        values = np.array(data_numeric.dropna(), dtype=float)

        max_value = np.max(values)
        min_value = np.min(values)
        median_value = np.median(values)
        mean_value = np.mean(values)

        percentiles = np.percentile(values, np.arange(0, 101, 5))

        result = max_value, min_value, median_value, mean_value, percentiles
    except KeyError:
        print(f"Column with name {column} does not exist")
    except Exception as exc:
        print(f"Something wrong: {exc}")
    finally:
        return result

def sort_region(data: DataFrame, region):
    data_sorted_region = data[data['region'] == region]
    return data_sorted_region if len(data_sorted_region) != 0 else None

def validate_region(data: DataFrame, region):
    result = None
    if region in data['region'].values:
        result = True
    return result

def get_amount_of_empty_rows(data: DataFrame):
    empty_rows = data.isnull().sum().sum()
    return empty_rows

def get_amount_of_bad_rows_by_column(data: DataFrame, column):
    bad_rows = data[data[column].str.contains(r'[a-zA-Z]')]
    return bad_rows

def get_regions(data: DataFrame):
    regions = data['region'].str.cat(sep=',').split(sep=',')
    regions_unique = set(regions)
    regions_unique.discard('region')
    filtered_regions_unique = sorted(regions_unique)
    return filtered_regions_unique