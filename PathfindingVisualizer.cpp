#include <iostream>
#include "raylib.h"
#include <vector>
#include <array>
#include <stack>
#include <queue>

const int LebarLayar = 1000;
const int TinggiLayar = 800;
const int HeaderHeight = 80; // Tinggi Navbar di atas

const int KolomSize = LebarLayar / 40; 
const int BarisSize = (TinggiLayar - HeaderHeight) / 40; 
const int UkuranCell = 40;

Color WebBgDark    = { 30, 34, 42, 255 };      // Navbar
Color WebBgLight   = { 240, 242, 245, 255 };   // Latar Labirin
Color WallColor    = { 44, 49, 58, 255 };      // Warna Tembok
Color CellVisited  = { 255, 255, 255, 255 };   // Lantai Maze

Color BtnColor     = { 97, 175, 239, 255 };    // Biru Tombol
Color BtnHover     = { 130, 195, 255, 255 };
Color BfsWater     = { 97, 175, 239, 60 };    // Air BFS
Color PathColorBFS = { 229, 192, 123, 200 };   // Kuning Jalur Akhir

Color BtnDFS       = { 224, 108, 117, 255 };   // Merah Tombol DFS
Color BtnHoverDFS  = { 240, 130, 140, 255 };
Color DfsWater     = { 224, 108, 117, 60 };   // Air DFS
Color PathColorDFS = { 198, 120, 221, 200 };   // Ungu Jalur Akhir

Color Djiktra      = { 130, 208, 217, 255 };   // Warna Tombol Djikstra
Color BtnHoverDjikstra  = { 150, 228, 237, 255 }; 
Color DjikstraWater     = { 130, 208, 217, 60 };    // Air Djikstra
Color PathColorDjikstra = { 152, 195, 121, 200 };   // Hijau Jalur Akhir Djikstra

int TargetBarisDraw = GetRandomValue(0 , BarisSize - 1), TargetKolomDraw = KolomSize - 1;
int StartBaris = GetRandomValue(0,BarisSize- 1), StartKolom = 0;

// Tambahkan Enum ini di atas (Global)
enum GameState {
    FASE_IDLE,
    FASE_GENERATE_MAZE,
    FASE_MENUNGGU,
    FASE_BFS_JALAN,
    FASE_DFS_JALAN,
    FASE_DJIKSTRA_JALAN
};

GameState statusGame = FASE_IDLE;

// Global Variabel untuk menyimpan dll



struct GridPos { // Struct untuk posisi baris dan kolom array
    int baris;
    int kolom;
};

struct NodePrioritas{
    GridPos Posisi;
    int Biaya;

    bool operator>(const NodePrioritas &Lainnya) const{
        return Biaya > Lainnya.Biaya;
    }
};

std::stack<GridPos> s; // menyimpan koordinat DFS maze Generator.
std::stack<GridPos> DFSstack; // meyimpan koordinat DFS Search path finding. 
std::priority_queue<NodePrioritas, std::vector<NodePrioritas>, std::greater<NodePrioritas>> pq; // menyimpan Koordinat Djikstra.
int CatatanWaktu[BarisSize][KolomSize];
std::queue<GridPos> q; // Menyimpan koordinat  BFS Search.
GridPos AsalUsulBFS[BarisSize][KolomSize]; // untuk menyimpan koordinat agar bisa backtrack koordinat BFS dan DFS agar ada path findingnya
std::vector<GridPos> JalurTerpendekBFS; // untuk  backtrack di fucntion rekonstruksi 
GridPos AsalUsulDFS[BarisSize][KolomSize]; // untuk menyimpan koordinat agar bisa backtrack koordinat BFS dan DFS agar ada path findingnya
std::vector<GridPos> JalurTerpendekDFS;
GridPos AsalUsulDjikstra[BarisSize][KolomSize]; // untuk menyimpan koordinat agar bisa backtrack koordinat Djikstra agar ada path findingnya
std::vector<GridPos> JalurTerpendekDjikstra; //untuk  backtrack di fucntion rekonstruksi 

// Fase 1 make a maze generator 
// -- DONE -- 
// membuat Struct / Object cell
struct cell{ 
    bool isVisited = false; // memastikan cell nya yang belum di kunjungi.
    // membuat wall nya.
    bool WallKanan = true;
    bool WallKiri = true;
    bool WallAtas = true;
    bool WallBawah = true;
};

cell Peta[BarisSize][KolomSize]; // Peta untuk grid nya
// Function  Inisialisasi posisi awal dari Maze Generation nya.
void InitGenerationMaze(int BarisAwal, int KolomAwal){
    Peta[BarisAwal][KolomAwal].isVisited = true;
    s.push({BarisAwal, KolomAwal});
}


void UpdateMazeStep(){ // update pergerakan per frame.
    std::vector<int> tetanga;
    if(s.empty()){
        return;
    }
    // ambil nilai saat ini.
    int BarisSaatIni = s.top().baris;
    int KolomSaatIni = s.top().kolom;
    //Untuk Cek tetangganya
    int Dx[4] = {0,0,1,-1};
    int Dy[4] = {1,-1,0,0};
    //Cari tetangga
    for(int i = 0; i < 4; i++){
        int TargetBaris = BarisSaatIni + Dy[i];
        int TargetKolom = KolomSaatIni + Dx[i];
        if(TargetBaris >= 0 && TargetBaris < BarisSize && 
            TargetKolom >= 0 && TargetKolom < KolomSize && Peta[TargetBaris][TargetKolom].isVisited != true){
                tetanga.push_back(i);
            }
        }
        if(tetanga.empty()){
            s.pop();
            return;
        }
        int random= GetRandomValue(0, tetanga.size() - 1);
        int ValidMove = tetanga[random];
        int TargetBaris = BarisSaatIni + Dy[ValidMove];
        int TargetKolom = KolomSaatIni + Dx[ValidMove];
        if(Dx[ValidMove] == 1){
            Peta[BarisSaatIni][KolomSaatIni].WallKanan = false;
            Peta[TargetBaris][TargetKolom].WallKiri = false;
            }
        if(Dx[ValidMove] == -1){
            Peta[BarisSaatIni][KolomSaatIni].WallKiri = false;
            Peta[TargetBaris][TargetKolom].WallKanan = false;
            }
        if(Dy[ValidMove] == 1 ){
            Peta[BarisSaatIni][KolomSaatIni].WallBawah = false;
                Peta[TargetBaris][TargetKolom].WallAtas = false;   
            }
            if(Dy[ValidMove] == -1){
                Peta[BarisSaatIni][KolomSaatIni].WallAtas = false;
                Peta[TargetBaris][TargetKolom].WallBawah = false;
            }
            // Buat cell yang di kunjugi jadi sudah di kunjungi statusnya
            Peta[TargetBaris][TargetKolom].isVisited = true;
            // masukan ke stack koordinat nya
            s.push({TargetBaris,TargetKolom});
}

void DrawPath(){
    // Gambar Start
    for(int baris = 0; baris < BarisSize; baris++){
        for(int kolom = 0; kolom < KolomSize; kolom++){
            cell& sel = Peta[baris][kolom];
            // GambarWall
            int x = kolom * UkuranCell;
            int y = (baris * UkuranCell) + HeaderHeight;
            if(sel.isVisited == true){
                DrawRectangle( x, y, UkuranCell, UkuranCell, WHITE);
            }
            if(sel.WallAtas == true){
                DrawLine(x, y, x + UkuranCell, y, WallColor);
            }if(sel.WallBawah == true){
                DrawLine(x, y + UkuranCell, x + UkuranCell, y + UkuranCell, WallColor);
            }if(sel.WallKanan == true){
                DrawLine(x + UkuranCell, y, x + UkuranCell, y + UkuranCell, WallColor);
            }if(sel.WallKiri == true){
                DrawLine(x, y, x, y + UkuranCell, WallColor);
            }       
        }
    }

    if(Peta[StartBaris][StartKolom].isVisited == true){
        int startX = StartKolom * UkuranCell;
        int startY = (StartBaris * UkuranCell) + HeaderHeight;
        DrawRectangle(startX, startY, UkuranCell, UkuranCell, RED);
    }
    
    // Gambar Target (Hijau)
    if(Peta[TargetBarisDraw][TargetKolomDraw].isVisited == true){
        int targetX = TargetKolomDraw * UkuranCell;
        int targetY = (TargetBarisDraw * UkuranCell) + HeaderHeight;
        DrawRectangle(targetX, targetY, UkuranCell, UkuranCell, GREEN);
    }
}   

//Fase 2 BFS Visualization As PathFinding Algorithm
// -- Done --;
// Membuat CekKondisi Sendiri untuk Algorithma ini.
bool BFSIsVisited[BarisSize][KolomSize] = {0};

// membuat rekonstuksi alur yang sudah di lewati BFS sampai ke finish 
void RekonstruksiJalurBFS(){
    int currRow = TargetBarisDraw;
    int currCol = TargetKolomDraw;
    while(currCol != StartKolom || currRow != StartBaris){
        JalurTerpendekBFS.push_back({currRow,currCol});
        int prevRow = AsalUsulBFS[currRow][currCol].baris;
        int prevCol = AsalUsulBFS[currRow][currCol].kolom;
    
        currRow = prevRow;
        currCol = prevCol;
    }

    JalurTerpendekBFS.push_back({StartBaris,StartKolom});
}

// inisialisasi posisi pertama BFS
void InitBFSSearch(int BarisAwal, int KolomAwal){
    BFSIsVisited[BarisAwal][KolomAwal] = 1;
    q.push({BarisAwal,KolomAwal}); // push pertama
}

//algoritma BFS untuk cek Setiap path 
void BFSSearch(){
    //Untuk Cek tetangganya
    int Dx[4] = {0,0,1,-1};
    int Dy[4] = {1,-1,0,0};
    
    if(!q.empty()){
        int BarisSaatIni = q.front().baris;
        int KolomSaatIni = q.front().kolom;
        q.pop();

        if(BarisSaatIni == TargetBarisDraw && KolomSaatIni == TargetKolomDraw){ // NYari Apakah nyetuh Finish
                    RekonstruksiJalurBFS();
                    statusGame = FASE_MENUNGGU;
                    return;
                }
                
        for(int i = 0; i < 4; i++){ // LOOP: Nyari seluruh tetangga BFS
        int TargetBaris = BarisSaatIni + Dy[i];
        int TargetKolom = KolomSaatIni + Dx[i];
            if(TargetBaris >= 0 && TargetBaris < BarisSize
                && TargetKolom >= 0 && TargetKolom < KolomSize && BFSIsVisited[TargetBaris][TargetKolom] != 1){
                    if(Dx[i] == 1 && Peta[BarisSaatIni][KolomSaatIni].WallKanan == false){
                        BFSIsVisited[TargetBaris][TargetKolom] = 1;
                        q.push({TargetBaris, TargetKolom});
                        AsalUsulBFS[TargetBaris][TargetKolom].baris = BarisSaatIni;
                        AsalUsulBFS[TargetBaris][TargetKolom].kolom = KolomSaatIni;
                    }else if(Dx[i] == -1 && Peta[BarisSaatIni][KolomSaatIni].WallKiri == false){
                        BFSIsVisited[TargetBaris][TargetKolom] = 1;
                        q.push({TargetBaris, TargetKolom});
                        AsalUsulBFS[TargetBaris][TargetKolom].baris = BarisSaatIni;
                        AsalUsulBFS[TargetBaris][TargetKolom].kolom = KolomSaatIni;
                    }else if(Dy[i] == -1 && Peta[BarisSaatIni][KolomSaatIni].WallAtas == false){
                        BFSIsVisited[TargetBaris][TargetKolom] = 1;
                        q.push({TargetBaris, TargetKolom});
                        AsalUsulBFS[TargetBaris][TargetKolom] = {BarisSaatIni,KolomSaatIni};
                    }else if(Dy[i] == 1 && Peta[BarisSaatIni][KolomSaatIni].WallBawah == false){
                        BFSIsVisited[TargetBaris][TargetKolom] = 1;
                        q.push({TargetBaris, TargetKolom});
                        AsalUsulBFS[TargetBaris][TargetKolom] = {BarisSaatIni,KolomSaatIni};
                    }
                }
            }
        } if(q.empty()){
            return;
     }
}
// Draw BFS searching 
void DrawBFS(){
    for(int baris = 0; baris < BarisSize; baris++){
        for(int kolom = 0; kolom < KolomSize; kolom++){
            int x = kolom * UkuranCell;
            int y = (baris * UkuranCell) + HeaderHeight;
            if(BFSIsVisited[baris][kolom] == 1){
                DrawRectangle(x,y, UkuranCell, UkuranCell, BfsWater);
            }
            
        }
    }
        for(int i = 0; i < JalurTerpendekBFS.size(); i++){
            int KoordinatBaris = JalurTerpendekBFS[i].baris;
            int KoordinatKolom = JalurTerpendekBFS[i].kolom;
            int pixelX = KoordinatKolom * UkuranCell;
            int pixelY = KoordinatBaris * UkuranCell + HeaderHeight;

        DrawRectangle(pixelX,pixelY,UkuranCell,UkuranCell,PathColorBFS);
        }
}

//Fase 3 DFS Search
bool DFSisVisited[BarisSize][KolomSize] = {0}; // Menyimpan posisi mana yang sudah di kunjungi

void InitDFSSearch(int BarisAwal, int KolomAwal){
    DFSisVisited[BarisAwal][KolomAwal] = 1;
    DFSstack.push({BarisAwal,KolomAwal}); // push pertama
}

void RekonstruksiJalurDFS(){
    int currRow = TargetBarisDraw;
    int currCol = TargetKolomDraw;

    while(currRow != StartBaris || currCol != StartKolom){
        JalurTerpendekDFS.push_back({currRow,currCol});
        int PrevRow = AsalUsulDFS[currRow][currCol].baris;
        int PrevCol = AsalUsulDFS[currRow][currCol].kolom;

        currRow = PrevRow;
        currCol = PrevCol;
    }
    JalurTerpendekDFS.push_back({StartBaris, StartKolom});
}

void DFSsearch(){
    if(DFSstack.empty()){
        return;
    }
    std::vector<int> TetanggaDFS;
    int BarisSaatIni = DFSstack.top().baris;
    int KolomSaatIni = DFSstack.top().kolom;
    if(BarisSaatIni == TargetBarisDraw && KolomSaatIni == TargetKolomDraw){
            RekonstruksiJalurDFS();
            statusGame = FASE_MENUNGGU;
            return;
        }
    //Untuk Cek tetangganya
    int Dx[4] = {0,0,1,-1};
    int Dy[4] = {1,-1,0,0};
    for(int i = 0; i < 4; i ++){
            int TargetBaris = BarisSaatIni + Dy[i];
            int TargetKolom = KolomSaatIni + Dx[i];
            if(TargetBaris >= 0 && TargetBaris < BarisSize && 
            TargetKolom >= 0 && TargetKolom < KolomSize && DFSisVisited[TargetBaris][TargetKolom] != 1){
                if(Dx[i] == 1 && Peta[BarisSaatIni][KolomSaatIni].WallKanan == false){
                    TetanggaDFS.push_back(i);
                }if(Dx[i] == -1 && Peta[BarisSaatIni][KolomSaatIni].WallKiri == false){
                    TetanggaDFS.push_back(i);
                }if(Dy[i] == 1 && Peta[BarisSaatIni][KolomSaatIni].WallBawah == false){
                    TetanggaDFS.push_back(i);
                }if(Dy[i] == -1 && Peta[BarisSaatIni][KolomSaatIni].WallAtas == false){
                    TetanggaDFS.push_back(i);
                }
            }
        }if(TetanggaDFS.empty()){
            DFSstack.pop();
            return;
        }
        int random = GetRandomValue(0, TetanggaDFS.size() - 1);
        int ValidMoveAcakDFS = TetanggaDFS[random];
        int TargetBaris = BarisSaatIni + Dy[ValidMoveAcakDFS];
        int TargetKolom = KolomSaatIni + Dx[ValidMoveAcakDFS];
        if(Dx[ValidMoveAcakDFS] == 1 && Peta[BarisSaatIni][KolomSaatIni].WallKanan == false){
            DFSisVisited[TargetBaris][TargetKolom] = 1;
            DFSstack.push({TargetBaris, TargetKolom});
            AsalUsulDFS[TargetBaris][TargetKolom].baris = BarisSaatIni;
            AsalUsulDFS[TargetBaris][TargetKolom].kolom = KolomSaatIni;
        }if(Dx[ValidMoveAcakDFS] == -1 && Peta[BarisSaatIni][KolomSaatIni].WallKiri == false){
            DFSisVisited[TargetBaris][TargetKolom] = 1;
            DFSstack.push({TargetBaris, TargetKolom});
            AsalUsulDFS[TargetBaris][TargetKolom].baris = BarisSaatIni;
            AsalUsulDFS[TargetBaris][TargetKolom].kolom = KolomSaatIni;
        }if(Dy[ValidMoveAcakDFS] == 1 && Peta[BarisSaatIni][KolomSaatIni].WallBawah == false){
            DFSisVisited[TargetBaris][TargetKolom] = 1;
            DFSstack.push({TargetBaris, TargetKolom});
            AsalUsulDFS[TargetBaris][TargetKolom].baris = BarisSaatIni;
            AsalUsulDFS[TargetBaris][TargetKolom].kolom = KolomSaatIni;
        }if(Dy[ValidMoveAcakDFS] == -1 && Peta[BarisSaatIni][KolomSaatIni].WallAtas == false){
            DFSisVisited[TargetBaris][TargetKolom] = 1;
            DFSstack.push({TargetBaris, TargetKolom});
            AsalUsulDFS[TargetBaris][TargetKolom].baris = BarisSaatIni;
            AsalUsulDFS[TargetBaris][TargetKolom].kolom = KolomSaatIni;
        }
}

void DrawDFS(){
    for(int baris = 0; baris < BarisSize; baris++){
        for(int kolom = 0; kolom < KolomSize; kolom++){
            int x = kolom * UkuranCell;
            int y = (baris * UkuranCell) + HeaderHeight;
            if(DFSisVisited[baris][kolom] == 1){
                DrawRectangle(x,y, UkuranCell, UkuranCell, DfsWater);
            }
            
        }
    }
        for(int i = 0; i < JalurTerpendekDFS.size(); i++){
            int CorRow = JalurTerpendekDFS[i].baris;
            int CorCol = JalurTerpendekDFS[i].kolom;
            int pixelX = CorCol * UkuranCell;
            int pixelY = CorRow * UkuranCell + HeaderHeight;

        DrawRectangle(pixelX,pixelY,UkuranCell,UkuranCell, PathColorDFS);
        }
}

// Fase 3 Djikstra

void InitDjikstra(int BarisAwal, int KolomAwal){
    for(int baris = 0; baris < BarisSize; baris++){
        for(int kolom = 0; kolom < KolomSize; kolom++){
            CatatanWaktu[baris][kolom] = 99999;
        }
    }

    CatatanWaktu[BarisAwal][KolomAwal] = 0;
    pq.push({{BarisAwal,KolomAwal}, 0 });
}

void RekonstruksiJalurDjikstra(){
    int currRow = TargetBarisDraw;
    int currCol = TargetKolomDraw;
    while(currCol != StartKolom || currRow != StartBaris){
        JalurTerpendekDjikstra.push_back({currRow,currCol});
        int prevRow = AsalUsulDjikstra[currRow][currCol].baris;
        int prevCol = AsalUsulDjikstra[currRow][currCol].kolom;
    
        currRow = prevRow;
        currCol = prevCol;
    }

    JalurTerpendekDjikstra.push_back({StartBaris,StartKolom});
}

void DjikstraSearch(){
    
    int Dx[4] = {0,0,1,-1};
    int Dy[4] = {1,-1,0,0};
    if(!pq.empty()){
        GridPos PosisiSaatIni = pq.top().Posisi;
        int BiayaSaatIni = pq.top().Biaya;
        pq.pop();
        int biayaBaru = BiayaSaatIni + 1; //  Karena Weight dari setiap arah array adalah 1.

        if(PosisiSaatIni.baris == TargetBarisDraw && PosisiSaatIni.kolom == TargetKolomDraw){
            RekonstruksiJalurDjikstra();
            statusGame = FASE_MENUNGGU;
            return;
        }
        for(int i = 0; i < 4; i++){
        int TargetBaris = PosisiSaatIni.baris + Dy[i];
        int TargetKolom = PosisiSaatIni.kolom+ Dx[i];
            if(TargetBaris >= 0 && TargetBaris < BarisSize
            && TargetKolom >= 0 && TargetKolom < KolomSize && biayaBaru < CatatanWaktu[TargetBaris][TargetKolom]){
                bool canMove = false;
                if(Dx[i] == 1 && Peta[PosisiSaatIni.baris][PosisiSaatIni.kolom].WallKanan == false) canMove = true;
                else if(Dx[i] == -1 && Peta[PosisiSaatIni.baris][PosisiSaatIni.kolom].WallKiri == false) canMove = true;
                else if(Dy[i] == 1 && Peta[PosisiSaatIni.baris][PosisiSaatIni.kolom].WallBawah == false) canMove = true;
                else if(Dy[i] == -1 && Peta[PosisiSaatIni.baris][PosisiSaatIni.kolom].WallAtas == false) canMove = true;
                if(canMove){
                    CatatanWaktu[TargetBaris][TargetKolom] = biayaBaru;
                    AsalUsulDjikstra[TargetBaris][TargetKolom] = {PosisiSaatIni.baris, PosisiSaatIni.kolom};
                    pq.push({{TargetBaris,TargetKolom}, biayaBaru});
                    }   
             }
        }  
    }
}

void DrawDjikstra(){
    for(int baris = 0; baris < BarisSize; baris++){
        for(int kolom = 0; kolom < KolomSize; kolom++){
            int x = kolom * UkuranCell;
            int y = (baris * UkuranCell) + HeaderHeight;
            if(CatatanWaktu[baris][kolom] < 99999){ 
                DrawRectangle(x,y, UkuranCell, UkuranCell, DjikstraWater);
            }
        }
    }
        for(int i = 0; i < JalurTerpendekDjikstra.size(); i++){
            int KoordinatBaris = JalurTerpendekDjikstra[i].baris;
            int KoordinatKolom = JalurTerpendekDjikstra[i].kolom;
            int pixelX = KoordinatKolom * UkuranCell;
            int pixelY = KoordinatBaris * UkuranCell + HeaderHeight;

        DrawRectangle(pixelX,pixelY,UkuranCell,UkuranCell,PathColorDjikstra);
        }
}

void ResetMaze() {
    while (!s.empty()) s.pop();
    while (!q.empty()) q.pop();
    while (!DFSstack.empty()) DFSstack.pop();
    // pq nggak punya fungsi .clear(), cara paling aman adalah me-reassign queue kosong
    pq = std::priority_queue<NodePrioritas, std::vector<NodePrioritas>, std::greater<NodePrioritas>>();

    JalurTerpendekBFS.clear();
    JalurTerpendekDFS.clear();
    JalurTerpendekDjikstra.clear();

    for (int baris = 0; baris < BarisSize; baris++) {
        for (int kolom = 0; kolom < KolomSize; kolom++) {
            Peta[baris][kolom].isVisited = false;
            Peta[baris][kolom].WallKanan = true;
            Peta[baris][kolom].WallKiri = true;
            Peta[baris][kolom].WallAtas = true;
            Peta[baris][kolom].WallBawah = true;

            BFSIsVisited[baris][kolom] = false;
            DFSisVisited[baris][kolom] = false;
            CatatanWaktu[baris][kolom] = 99999;
        }
    }
}


// CLEAN UI SYSTEM
struct CustomButton {
    Rectangle rec;
    const char* text;
    Color color;
    Color hoverColor;
    bool enabled;

    bool IsHovered() {
        return CheckCollisionPointRec(GetMousePosition(), rec);
    }
    
    bool IsClicked() {
        return IsHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
    
    void Draw() {
        Color c = GRAY;
        if (enabled) {
            c = IsHovered() ? hoverColor : color;
        }
        // Pakai border-radius / melengkung supaya modern
        DrawRectangleRounded(rec, 0.4f, 10, c);
        
        int textWidth = MeasureText(text, 18);
        DrawText(text, rec.x + (rec.width - textWidth) / 2, rec.y + (rec.height - 18) / 2, 18, WHITE);
    }
};

void DrawModernUI() {
    // Background Header
    DrawRectangle(0, 0, LebarLayar, HeaderHeight, WebBgDark);
    DrawText("MAZE VISUALIZER", 10, 28, 20, WHITE);

    bool isIdleOrWaiting = (statusGame == FASE_IDLE || statusGame == FASE_MENUNGGU);

    // Bikin tombol menggunakan struct yang sudah rapi (posisi X aku geser dikit biar pas 4 tombol)
    CustomButton btnGen = { {240, 20, 150, 50}, "Generate Maze", BtnColor, BtnHover, isIdleOrWaiting };
    CustomButton btnBFS = { {400, 20, 110, 50}, "Start BFS", BtnColor, BtnHover, statusGame == FASE_MENUNGGU };
    CustomButton btnDFS = { {520, 20, 110, 50}, "Start DFS", BtnDFS, BtnHoverDFS, statusGame == FASE_MENUNGGU };
    CustomButton btnDjikstra = { {640, 20, 140, 50}, "Start Djikstra", Djiktra, BtnHoverDjikstra, statusGame == FASE_MENUNGGU };

    btnGen.Draw();
    btnBFS.Draw();
    btnDFS.Draw();
    btnDjikstra.Draw();

    // Logic Tombol
    if (btnGen.IsClicked() && btnGen.enabled) {
        ResetMaze();
        StartBaris = GetRandomValue(0, BarisSize - 1);
        TargetBarisDraw = GetRandomValue(0, BarisSize - 1);
        InitGenerationMaze(StartBaris, StartKolom);
        statusGame = FASE_GENERATE_MAZE;
    }

    if (btnBFS.IsClicked() && btnBFS.enabled) {
        JalurTerpendekBFS.clear();
        JalurTerpendekDFS.clear(); // Bersihkan garis DFS jika ada
        JalurTerpendekDjikstra.clear(); 
        for (int b = 0; b < BarisSize; b++) 
            for (int k = 0; k < KolomSize; k++) BFSIsVisited[b][k] = false;
        while (!q.empty()) q.pop();
        
        InitBFSSearch(StartBaris, StartKolom);
        statusGame = FASE_BFS_JALAN;
    }

    if (btnDFS.IsClicked() && btnDFS.enabled) {
        JalurTerpendekDFS.clear();
        JalurTerpendekBFS.clear(); // Bersihkan garis BFS jika ada
        JalurTerpendekDjikstra.clear();
        for (int b = 0; b < BarisSize; b++) 
            for (int k = 0; k < KolomSize; k++) DFSisVisited[b][k] = false;
        while (!DFSstack.empty()) DFSstack.pop();
        
        InitDFSSearch(StartBaris, StartKolom);
        statusGame = FASE_DFS_JALAN;
    }
    
    // Logic Tombol Djikstra
    if (btnDjikstra.IsClicked() && btnDjikstra.enabled) {
        JalurTerpendekDFS.clear();
        JalurTerpendekBFS.clear();
        JalurTerpendekDjikstra.clear();
        
        // Kosongkan priority queue
        pq = std::priority_queue<NodePrioritas, std::vector<NodePrioritas>, std::greater<NodePrioritas>>();
        
        InitDjikstra(StartBaris, StartKolom);
        statusGame = FASE_DJIKSTRA_JALAN;
    }

    // Teks Status (Pojok Kanan)
    const char* statusText = "Ready";
    Color statusColor = GRAY;

    switch (statusGame) {
        case FASE_IDLE:             statusText = "Ready"; statusColor = LIGHTGRAY; break;
        case FASE_GENERATE_MAZE:    statusText = "Building Maze..."; statusColor = YELLOW; break;
        case FASE_BFS_JALAN:        statusText = "BFS Searching..."; statusColor = BtnHover; break;
        case FASE_DFS_JALAN:        statusText = "DFS Searching..."; statusColor = BtnHoverDFS; break;
        case FASE_DJIKSTRA_JALAN:   statusText = "Djikstra Search..."; statusColor = BtnHoverDjikstra; break;
        case FASE_MENUNGGU:
            if (!JalurTerpendekBFS.empty()) { statusText = "BFS Done!"; statusColor = GREEN; }
            else if (!JalurTerpendekDFS.empty()) { statusText = "DFS Done!"; statusColor = GREEN; }
            else if (!JalurTerpendekDjikstra.empty()) { statusText = "Djikstra Done!"; statusColor = GREEN; }
            else { statusText = "Maze Ready"; statusColor = GREEN; }
            break;
    }
    
    DrawText(statusText, 820, 30, 20, statusColor);
}


// MAIN LOOP
int main() {
    InitWindow(LebarLayar, TinggiLayar, "Pathfinding Visualizer");
    SetTargetFPS(60); // 60 Node per detik saat animasi jalan

    while (!WindowShouldClose()) {
        
        // UPDATE LOGIC
        switch (statusGame) {
            case FASE_GENERATE_MAZE:
                UpdateMazeStep();
                // Opsional: jalankan beberapa kali per frame biar gerakannya lebih cepat
                UpdateMazeStep(); UpdateMazeStep(); UpdateMazeStep(); 
                if (s.empty()) statusGame = FASE_MENUNGGU;
                break;
            case FASE_BFS_JALAN:
                BFSSearch();
                break;
            case FASE_DFS_JALAN:
                DFSsearch();
                break;
            case FASE_DJIKSTRA_JALAN: // Tambahkan trigger update
                DjikstraSearch();
                break;
            default: break;
        }

        // DRAWING LOGIC
        BeginDrawing();
        ClearBackground(WebBgLight);
        
        DrawPath(); // Gambar base peta

        // BUG FIX: Sekarang animasi searching digambar BAHKAN sebelum jalurnya ketemu
        if (statusGame == FASE_BFS_JALAN || !JalurTerpendekBFS.empty()) DrawBFS();
        if (statusGame == FASE_DFS_JALAN || !JalurTerpendekDFS.empty()) DrawDFS();
        if (statusGame == FASE_DJIKSTRA_JALAN || !JalurTerpendekDjikstra.empty()) DrawDjikstra();

        DrawModernUI();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}