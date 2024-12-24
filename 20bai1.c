#include<stdio.h>
struct Sach {
    char maSach[20];
    char tenSach[50];
    char tacGia[50];
    float giaTien;
    char theLoai[30];
};

void nhapSach(struct Sach *s) {
    printf("Nhap ma sach: ");
    scanf("%s", s->maSach);
    printf("Nhap ten sach: ");
    scanf(" %[^\n]", s->tenSach);
    printf("Nhap tac gia: ");
    scanf(" %[^\n]", s->tacGia);
    printf("Nhap gia tien: ");
    scanf("%f", &s->giaTien);
    printf("Nhap the loai: ");
    scanf(" %[^\n]", s->theLoai);
}

void hienThiSach(struct Sach s) {
    printf("Ma sach: %s\n", s.maSach);
    printf("Ten sach: %s\n", s.tenSach);
    printf("Tac gia: %s\n", s.tacGia);
    printf("Gia tien: %.2f\n", s.giaTien);
    printf("The loai: %s\n", s.theLoai);
}

void hienThiTatCaSach(struct Sach ds[], int sl) {
    for (int i = 0; i < sl; i++) {
        printf("\nSach thu %d:\n", i + 1);
        hienThiSach(ds[i]);
    }
}

void themSach(struct Sach ds[], int *sl, int vt) {
    if (*sl >= 100) {
        printf("Khong the them sach. Thu vien da day.\n");
        return;
    }
    for (int i = *sl; i > vt; i--) {
        ds[i] = ds[i - 1];
    }
    nhapSach(&ds[vt]);
    (*sl)++;
}

void xoaSach(struct Sach ds[], int *sl, char ma[]) {
    int vt = -1;
    for (int i = 0; i < *sl; i++) {
        if (strcmp(ds[i].maSach, ma) == 0) {
            vt = i;
            break;
        }
    }
    if (vt == -1) {
        printf("Khong tim thay sach voi ma %s.\n", ma);
        return;
    }
    for (int i = vt; i < *sl - 1; i++) {
        ds[i] = ds[i + 1];
    }
    (*sl)--;
}

void capNhatSach(struct Sach ds[], int sl, char ma[]) {
    int vt = -1;
    for (int i = 0; i < sl; i++) {
        if (strcmp(ds[i].maSach, ma) == 0) {
            vt = i;
            break;
        }
    }
    if (vt == -1) {
        printf("Khong tim thay sach voi ma %s.\n", ma);
        return;
    }
    nhapSach(&ds[vt]);
}

void sapXepSach(struct Sach ds[], int sl, int tang) {
    for (int i = 0; i < sl - 1; i++) {
        for (int j = i + 1; j < sl; j++) {
            if ((tang && ds[i].giaTien > ds[j].giaTien) || (!tang && ds[i].giaTien < ds[j].giaTien)) {
                struct Sach temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

void timKiemSach(struct Sach ds[], int sl, char ten[]) {
    for (int i = 0; i < sl; i++) {
        if (strstr(ds[i].tenSach, ten) != NULL) {
            hienThiSach(ds[i]);
        }
    }
}

int main() {
    struct Sach ds[100];
    int sl = 0;
    int luaChon;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach.\n");
        printf("2. Hien thi thong tin sach.\n");
        printf("3. Them sach vao vi tri.\n");
        printf("4. Xoa sach theo ma sach.\n");
        printf("5. Cap nhat thong tin sach theo ma sach.\n");
        printf("6. Sap xep sach theo gia (tang/giam).\n");
        printf("7. Tim kiem sach theo ten sach.\n");
        printf("8. Thoat.\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);
        switch (luaChon) {
            case 1:
                printf("Nhap so luong sach: ");
                scanf("%d", &sl);
                for (int i = 0; i < sl; i++) {
                    printf("\nNhap thong tin sach thu %d:\n", i + 1);
                    nhapSach(&ds[i]);
                }
                break;
            case 2:
                hienThiTatCaSach(ds, sl);
                break;
            case 3: {
                int vt;
                printf("Nhap vi tri can them: ");
                scanf("%d", &vt);
                if (vt < 0 || vt > sl) {
                    printf("Vi tri khong hop le.\n");
                } else {
                    themSach(ds, &sl, vt);
                }
                break;
            }
            case 4: {
                char ma[20];
                printf("Nhap ma sach can xoa: ");
                scanf("%s", ma);
                xoaSach(ds, &sl, ma);
                break;
            }
            case 5: {
                char ma[20];
                printf("Nhap ma sach can cap nhat: ");
                scanf("%s", ma);
                capNhatSach(ds, sl, ma);
                break;
            }
            case 6: {
                int tang;
                printf("Nhap 1 de sap xep tang, 0 de sap xep giam: ");
                scanf("%d", &tang);
                sapXepSach(ds, sl, tang);
                break;
            }
            case 7: {
                char ten[50];
                printf("Nhap ten sach can tim: ");
                scanf(" %[^\n]", ten);
                timKiemSach(ds, sl, ten);
                break;
            }
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 8);
    return 0;
}

