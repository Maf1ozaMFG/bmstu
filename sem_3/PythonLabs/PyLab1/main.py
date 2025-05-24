from input_module import read_csv_file, read_region, read_column
from logic_module import sort_region, calculate_stats
from output_module import print_calculated_stats, print_data_by_region, print_bad_rows, print_regions, print_data


def main():
    filepath = input("Enter filepath: ")

    data = read_csv_file(filepath)

    if data is None: return
    print_regions(data)

    region = read_region(data)

    data_sorted_region = sort_region(data, region)

    if data_sorted_region is None: return

    print_data_by_region(data_sorted_region)
    column = read_column(region)
    print_bad_rows(data_sorted_region, column)
    stats = calculate_stats(data_sorted_region, column)

    if stats is None: return

    max_value, min_value, median_value, average_value, percentiles = stats
    print_calculated_stats(max_value, min_value, median_value, average_value, percentiles)



if __name__ == "__main__":
    main()

#C:\Program Files\PythonEducation\russian_demography.csv
#C:\Program Files\PythonEducation\empty_rows.csv