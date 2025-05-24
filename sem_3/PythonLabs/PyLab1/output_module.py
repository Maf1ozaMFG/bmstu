from pandas import DataFrame

from logic_module import get_amount_of_empty_rows, get_regions, get_amount_of_bad_rows_by_column


def print_calculated_stats(max, min, median, aver, perc):
    print(f'\nStats:\n'
          f'Maximum: {max:.6f}\n'
          f'Minimum: {min:.6f}\n'
          f'Median: {median:.6f}\n'
          f'Average: {aver:.6f}\n')
    print('Percentiles: ')

    number = 0
    for j in perc:
        print(f'{number}. {j:.6f}')
        number += 5

def print_data_by_region(data: DataFrame):
    print('Data by region:')
    print(data)

def print_data(data: DataFrame):
    print(data)

def print_bad_rows(data: DataFrame, column):
    bad_rows = get_amount_of_bad_rows_by_column(data, column)
    rows = get_amount_of_empty_rows(data) + len(bad_rows)
    print(f'\nFailed rows:\n{rows}')

def print_regions(data: DataFrame):
    sorted_regions_unique = get_regions(data)
    print('\nAvailable regions:\n')
    for number, region_name in enumerate(sorted_regions_unique, start = 1):
        print(f'{number}. {region_name}')



