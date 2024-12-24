#include <stdio.h>
struct SanPham {
    char maSanPham[20];
    char tenSanPham[50];
    float giaNhap;
    float giaBan;
    int soLuong;
};
void nhapSanPham(struct SanPham *sp) {
    printf("Nhap ma san pham: ");
    scanf("%s", sp->maSanPham);
    printf("Nhap ten san pham: ");
    scanf(" %[^\n]", sp->tenSanPham);
    printf("Nhap gia nhap: ");
    scanf("%f", &sp->giaNhap);
    printf("Nhap gia ban: ");
    scanf("%f", &sp->giaBan);
    printf("Nhap so luong: ");
    scanf("%d", &sp->soLuong);
}

void hienThiSanPham(struct SanPham sp) {
    printf("Ma san pham: %s\n", sp.maSanPham);
    printf("Ten san pham: %s\n", sp.tenSanPham);
    printf("Gia nhap: %.2f\n", sp.giaNhap);
    printf("Gia ban: %.2f\n", sp.giaBan);
    printf("So luong: %d\n", sp.soLuong);
}

void hienThiTatCaSanPham(struct SanPham ds[], int sl) {
    for (int i = 0; i < sl; i++) {
        printf("\nSan pham thu %d:\n", i + 1);
        hienThiSanPham(ds[i]);
    }
}

void nhapSanPhamVaoMang(struct SanPham ds[], int *sl, float *doanhThu) {
    struct SanPham sp;
    nhapSanPham(&sp);
    int tonTai = 0;
    for (int i = 0; i < *sl; i++) {
        if (strcmp(ds[i].maSanPham, sp.maSanPham) == 0) {
            ds[i].soLuong += sp.soLuong;
            tonTai = 1;
            break;
        }
    }
    if (!tonTai) {
        ds[*sl] = sp;
        (*sl)++;
    }
    *doanhThu -= sp.soLuong * sp.giaNhap;
}

void capNhatSanPham(struct SanPham ds[], int sl, char ma[]) {
    int vt = -1;
    for (int i = 0; i < sl; i++) {
        if (strcmp(ds[i].maSanPham, ma) == 0) {
            vt = i;
            break;
        }
    }
    if (vt == -1) {
        printf("Khong tim thay san pham voi ma %s.\n", ma);
        return;
    }
    nhapSanPham(&ds[vt]);
}

void sapXepSanPham(struct SanPham ds[], int sl, int tang) {
    for (int i = 0; i < sl - 1; i++) {
        for (int j = i + 1; j < sl; j++) {
            if ((tang && ds[i].giaBan > ds[j].giaBan) || (!tang && ds[i].giaBan < ds[j].giaBan)) {
                struct SanPham temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

void timKiemSanPham(struct SanPham ds[], int sl, char ten[]) {
    for (int i = 0; i < sl; i++) {
        if (strstr(ds[i].tenSanPham, ten) != NULL) {
            hienThiSanPham(ds[i]);
        }
    }
}

void banSanPham(struct SanPham ds[], int sl, char ma[], int soLuongBan, float *doanhThu) {
    int vt = -1;
    for (int i = 0; i < sl; i++) {
        if (strcmp(ds[i].maSanPham, ma) == 0) {
            vt = i;
            break;
        }
    }
    if (vt == -1) {
        printf("Khong tim thay san pham voi ma %s.\n", ma);
        return;
    }
    if (ds[vt].soLuong == 0) {
        printf("Het hang.\n");
        return;
    }
    if (soLuongBan > ds[vt].soLuong) {
        printf("Khong con du hang.\n");
        return;
    }
    ds[vt].soLuong -= soLuongBan;
    *doanhThu += soLuongBan * ds[vt].giaBan;
}

int main() {
    struct SanPham ds[100];
    int sl = 0;
    float doanhThu = 0;
    int luaChon;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham.\n");
        printf("2. Hien thi danh sach san pham.\n");
        printf("3. Nhap san pham.\n");
        printf("4. Cap nhat thong tin san pham.\n");
        printf("5. Sap xep san pham theo gia (tang/giam).\n");
        printf("6. Tim kiem san pham.\n");
        printf("7. Ban san pham (co the nhap so luong can ban).\n");
        printf("8. Doanh thu hien tai.\n");
        printf("9. Thoat.\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);
        switch (luaChon) {
            case 1:
                printf("Nhap so luong san pham: ");
                scanf("%d", &sl);
                for (int i = 0; i < sl; i++) {
                    printf("\nNhap thong tin san pham thu %d:\n", i + 1);
                    nhapSanPham(&ds[i]);
                }
                break;
            case 2:
                hienThiTatCaSanPham(ds, sl);
                break;
            case 3:
                nhapSanPhamVaoMang(ds, &sl, &doanhThu);
                break;
            case 4: {
                char ma[20];
                printf("Nhap ma san pham can cap nhat: ");
                scanf("%s", ma);
                capNhatSanPham(ds, sl, ma);
                break;
            }
            case 5: {
                int tang;
                printf("Nhap 1 de sap xep tang, 0 de sap xep giam: ");
                scanf("%d", &tang);
                sapXepSanPham(ds, sl, tang);
                break;
            }
            case 6: {
                char ten[50];
                printf("Nhap ten san pham can tim: ");
                scanf(" %[^\n]", ten);
                timKiemSanPham(ds, sl, ten);
                break;
            }
            case 7: {
                char ma[20];
                int soLuongBan;
                printf("Nhap ma san pham can ban: ");
                scanf("%s", ma);
                printf("Nhap so luong can ban: ");
                scanf("%d", &soLuongBan);
                banSanPham(ds, sl, ma, soLuongBan, &doanhThu);
                break;
            }
            case 8:
                printf("Doanh thu hien tai: %.2f\n", doanhThu);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 9);
    return 0;
}
