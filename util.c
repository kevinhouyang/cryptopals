int hex_to_int(char);
char int_to_base64(int);

void hex_to_base64(char *dest, char *in) {
    int a, b, c;
    a = hex_to_int(in[0]);
    b = hex_to_int(in[1]);
    c = hex_to_int(in[2]);

    unsigned d = a << 8 | b << 4 | c;

    unsigned mask1 = 63;
    unsigned mask2 = mask1 << 6;

    int e = (d & mask2) >> 6;
    int f = d & mask1;

    char g = int_to_base64(e);
    char h = int_to_base64(f);

    dest[0] = g;
    dest[1] = h;

    return;
}

int hex_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    } else {
        return -1;
    }
}

char int_to_hex(int i)
{
    if (i >= 0 && i <= 9) {
        return i + '0';
    } else if (i >= 10 && i <= 15) {
        return i + 'a' - 10;
    } else {
        return -1;
    }
}

char int_to_base64(int i) {
    if (i >= 0 && i <= 25) {
        return i + 'A';
    } else if (i >= 26 && i <= 51) {
        return i + 'a' - 26;
    } else if (i >= 52 && i <= 62) {
        return i + '0' - 52;
    } else {
        return -1;
    }
}
