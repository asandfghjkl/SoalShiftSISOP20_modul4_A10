# SoalShiftSISOP20_modul4_A10
**Sandra Agnes Oktaviana  (05111840000124)**

**Adrian Danindra Indarto (05111840000068)**

### penyelesaian & penjelasan soal

**1) Sebuah folder akan dilakukan enkripsi jika terdapat encv1 di awal nama foldernya dengan menggunakan enkripsi versi 1.**

Program membaca nama folder dam mencocokkan awalan folder dengan string "encv1" ketika telah dilakukan rename atau folder itu merupakan folder baru. Jika awalan string cocok, maka untuk setiap file akan dienkripsi, program akan melakukan rekursi untuk mengecek folder jika terdapat folder di dalam folder yang dienkripsi, mengambil nama file dan mengenkripsi nama file atau folder itu, dan mengenkripsi nama file itu. Program mengambil nama file dan merubahnya sebelum digunakan untuk nama file baru dengan menggunakan caesar cipher dengan key 10. jika folder direname sehingga menghilangkan nama encv1 di foldernya, maka semua file akan didekripsi. Semua operasi rename akan dicatat di dalam log dengan level info.

**4) Log Perubahan**

Fungsi ini membutuhkan level dan deskripsi dari operasi yang memanggil fungsi ini. Fungsi ini pada awalnya akan membuka file log bernama fs.log. Lalu program ini mengambil struct waktu dari sistem dan mengubahnya ke dalam string, lalu string waktu ini digunakan untuk menambah informasi ke deskripsi yang akan dituliskan ke file log. file ditutup setelah penulisan isi string deskripsi ke log selesai.
