# SoalShiftSISOP20_modul4_A10
**Sandra Agnes Oktaviana  (05111840000124)**

**Adrian Danindra Indarto (05111840000068)**

## table of contents
* [soal1](https://github.com/asandfghjkl/SoalShiftSISOP20_modul4_A10#soal1)
* [soal4](https://github.com/asandfghjkl/SoalShiftSISOP20_modul4_A10#soal4)

## source code [ssfs.c](https://github.com/asandfghjkl/SoalShiftSISOP20_modul4_A10/blob/master/ssfs.c)

## soal1
Enkripsi versi 1:
- Jika sebuah direktori dibuat dengan awalan “encv1_”, maka direktori tersebut akan menjadi direktori terenkripsi menggunakan metode enkripsi v1.
- Jika sebuah direktori di-rename dengan awalan “encv1_”, maka direktori tersebut akan menjadi direktori terenkripsi menggunakan metode enkripsi v1.
- Apabila sebuah direktori terenkripsi di-rename menjadi tidak terenkripsi, maka isi adirektori tersebut akan terdekrip.
- Setiap pembuatan direktori terenkripsi baru (mkdir ataupun rename) akan tercatat ke sebuah database/log berupa file.
- Semua file yang berada dalam direktori ter enkripsi menggunakan caesar cipher dengan key.
  ```
  9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO
  ```
  Misal kan ada file bernama “kelincilucu.jpg” dalam directory FOTO_PENTING, dan key yang dipakai adalah 10
  “encv1_rahasia/FOTO_PENTING/kelincilucu.jpg” => “encv1_rahasia/ULlL@u]AlZA(/g7D.|_.Da_a.jpg
  Note : Dalam penamaan file ‘/’ diabaikan, dan ekstensi tidak perlu di encrypt.
- Metode enkripsi pada suatu direktori juga berlaku kedalam direktori lainnya yang ada didalamnya.

### penyelesaian & penjelasan soal

Program membaca nama folder dam mencocokkan awalan folder dengan string "encv1_" ketika telah dilakukan rename atau folder itu merupakan folder baru. Jika awalan string cocok, maka untuk setiap file akan dienkripsi, program akan melakukan rekursi untuk mengecek folder jika terdapat folder di dalam folder yang dienkripsi, mengambil nama file dan mengenkripsi nama file atau folder itu, dan mengenkripsi nama file itu. Program mengambil nama file dan merubahnya sebelum digunakan untuk nama file baru dengan menggunakan caesar cipher dengan key 10. jika folder direname sehingga menghilangkan nama encv1 di foldernya, maka semua file akan didekripsi. Semua operasi rename akan dicatat di dalam log dengan level info.

terdapat 12 fungsi yang dideklarasikan dengan fungsi `struct fuse_operations` berikut:
```
static struct fuse_operations xmp_oper = {
  	.getattr  = xmp_getattr,
  	.readdir  = xmp_readdir,
  	.mkdir    = xmp_mkdir,
  	.rmdir    = xmp_rmdir,
  	.mknod    = xmp_mknod,
  	.unlink   = xmp_unlink,
  	.rename   = xmp_rename,
  	.open     = xmp_open,
  	.read     = xmp_read,
  	.write    = xmp_write,
  	.truncate = xmp_truncate,
};
```

fungsi FUSE tersebut digunakan untuk menampilkan isi folder `"/home/sun/Documents"`, sehingga dideklarasikan:
```
static  const  char *dirpath = "/home/sun/Documents";
```

dan untuk key caesar cipher dideklarasikan sbb:
```
char key[100] = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
```

- Fungsi encrypt untuk enkripsi dalam folder "encv1_"
```
void encrypt(char *path) {
  int start = 0, end = strlen(path);

  for (int i=strlen(path); i>=0; i--) { // cari extension
    if(path[i] == '/') break;
    if(path[i] == '.') {
      end = i - 1;
      break;
    }
  }

  for(int i=1; i<strlen(path); i++) {	// cari pathfile
    if(path[i] == '/') {
      start = i;
      break;
    }
  }

  for(int i=start; i <= end; i++) {	// enkripsi namefile
    if(path[i] == '/') continue;

    for(int j = strlen(key)-1; j>=0; j--) {
    	if(path[i] == key[j]) {
        	path[i] = key[j + 10];
        	break;
      	}
    }
  }
}
```

- Fungsi descrypt untuk deskripsi dalam folder "encv1_" apabila dilakukan rename folder tidak lagi "encv1_"
```
void decrypt(char *path) {
  int start = 0, end = strlen(path);

  for(int i=1; i<strlen(path); i++) {	// cari pathfile
    if(path[i] == '/' || path[i + 1] == '\0') {
      start = i + 1;
      break;
    }
  }

  for(int i=strlen(path); i>=0; i--) {	// cari extension
    if(path[i] == '.') {
      end = i - 1;
      break;
    }
  }

  for(int i=start; i <= end; i++) {	// dekripsi namefile
    if(path[i] == '/') continue;

    for(int j = strlen(key)-1; j>=0; j--) {
    	if(path[i] == key[j]) {
        	path[i] = key[j - 10];
        	break;
      	}
    }
  }
}
```

Hasil Run:
* isi folder encv1_tes

![soal1](https://github.com/asandfghjkl/SoalShiftSISOP20_modul4_A10/blob/master/pics/soal1.png)

* isi folder encv1_tes hasil enkripsi 
![soal1encv1](https://github.com/asandfghjkl/SoalShiftSISOP20_modul4_A10/blob/master/pics/soal1encv1.png)

## soal4
Log system:

- Sebuah berkas nantinya akan terbentuk bernama "fs.log" di direktori *home* pengguna (/home/[user]/fs.log) yang berguna menyimpan daftar perintah system call yang telah dijalankan.
- Agar nantinya pencatatan lebih rapi dan terstruktur, log akan dibagi menjadi beberapa level yaitu INFO dan WARNING.
- Untuk log level WARNING, merupakan pencatatan log untuk syscall rmdir dan unlink. Sisanya, akan dicatat dengan level INFO.
- Format untuk logging yaitu:
  ```
  [LEVEL]::[yy][mm][dd]-[HH]:[MM]:[SS]::[CMD]::[DESC ...]
  ```
  LEVEL    : Level logging.
  
  yy   	   : Tahun dua digit.
  
  mm    	 : Bulan dua digit.
  
  dd    	 : Hari dua digit
  
  HH    	 : Jam dua digit
  
  MM    	 : Menit dua digit
  
  SS    	 : Detik dua digit
  
  CMD      : System call yang terpanggil
  
  DESC     : Deskripsi tambahan (bisa lebih dari satu, dipisahkan dengan ::)

Contoh format logging nantinya seperti:
  ```
  INFO::200419-18:29:28::MKDIR::/iz1
  
  INFO::200419-18:29:33::CREAT::/iz1/yena.jpg
  
  INFO::200419-18:29:33::RENAME::/iz1/yena.jpg::/iz1/yena.jpeg
  ```
  
### penyelesaian & penjelasan soal

Fungsi ini membutuhkan level dan deskripsi dari operasi yang memanggil fungsi ini. Fungsi ini pada awalnya akan membuka file log bernama fs.log. Lalu program ini mengambil struct waktu dari sistem dan mengubahnya ke dalam string, lalu string waktu ini digunakan untuk menambah informasi ke deskripsi yang akan dituliskan ke file log. file ditutup setelah penulisan isi string deskripsi ke log selesai.

- fungsi logFile 
```
void logFile(char *level, char *desc) {
  	time_t rawtime = time(NULL);
  	struct tm *info;
  	info = localtime(&rawtime);

  	char time[100];
  	strftime(time, sizeof(time), "%y%m%d-%H:%M:%S", info);

  	char log[100];
  	sprintf(log, "%s%s%s\n", level, time, desc);

  	FILE *fp;
  	fp = fopen("/home/sun/fs.log", "a+");
  	fputs(log, fp);

  	fclose(fp);
}
```

setiap fungsi akan disertakan call fungsi logFile untuk pencatatan log.
contoh dalam fungsi `xmp_getattr`:
```
char desc[128];
        sprintf(desc, "::GETATTR::%s", fpath);
        logFile("INFO::", desc);
```
perlu diingat untuk log level WARNING, merupakan pencatatan log untuk syscall rmdir dan unlink. Sisanya, akan dicatat dengan level INFO.


hasil fs.log
![fslog](https://github.com/asandfghjkl/SoalShiftSISOP20_modul4_A10/blob/master/pics/fslog.png)
