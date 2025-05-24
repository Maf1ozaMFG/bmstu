int myStrlen(const char* s) {
    unsigned i;
    for (i = 0; s[i]; i++);
    return i;
}
