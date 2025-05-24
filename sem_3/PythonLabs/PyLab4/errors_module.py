def print_error_region():
    print("\nRegion does not exist!")

class ExceptionDescription:
    file_not_found = "\nFile is not exist!"
    empty_data = "\nFile is empty!"
    parser_error = ("\nFile is unreadable. "
                    "Check CSV format!")
    big_file = "\nFile is too large!"

class BigDataError(Exception):
    pass



