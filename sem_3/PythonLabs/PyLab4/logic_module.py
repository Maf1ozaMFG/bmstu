import numpy as np
from pandas import DataFrame
from sklearn.metrics import r2_score, mean_squared_error


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

# def get_amount_of_bad_rows_by_column(data: DataFrame, column):
#     bad_rows = data[data[column].str.contains(r'[a-zA-Z]')]
#     return bad_rows

def get_regions(data: DataFrame):
    regions = data['region'].str.cat(sep=',').split(sep=',')
    regions_unique = set(regions)
    regions_unique.discard('region')
    filtered_regions_unique = sorted(regions_unique)
    return filtered_regions_unique

def evaluate_model(y_test, y_pred):
    mse = mean_squared_error(y_test, y_pred)
    r2 = r2_score(y_test, y_pred)
    print(f"Mean Squared Error: {mse}")
    print(f"R^2 Score: {r2}")

def predict(choice, model):
    choice = np.array([[choice]])
    prediction = model.predict(choice)
    return prediction[0]



