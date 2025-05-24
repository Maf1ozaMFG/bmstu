int myStrcmp(const char* a, const char* b) {
    unsigned i;
    for (i = 0; a[i] && a[i] == b[i]; i++);
    return a[i] - b[i];
}
