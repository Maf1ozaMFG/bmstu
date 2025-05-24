from pandas import DataFrame

from logic_module import get_amount_of_empty_rows, get_regions

def print_data_by_region(data: DataFrame):
    print('Data by region:')
    print(data)

def print_data(data: DataFrame):
    print(data)

def print_empty_rows(data: DataFrame):
    rows = get_amount_of_empty_rows(data)
    print(f'\nFailed rows:\n{rows}')

def print_regions(data: DataFrame):
    sorted_regions_unique = get_regions(data)
    print('\nAvailable regions:\n')
    for number, region_name in enumerate(sorted_regions_unique, start = 1):
        print(f'{number}. {region_name}')



