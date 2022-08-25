#include "graphics/ivec.h"

#include "graphics/sys.h"
//|
//| ivec : n-dimensional ivector
//|




namespace graphics {



const int ivec2::n = 2;




//| I/O
void print(const ivec2& a)
{
    LOG("(%d", a[0]);
    for(int i = 1; i < 2;++i){
	LOG(" %d", a[i]);
    }
    LOG(") ");
}

void store(FILE* fp, const ivec2& v)
{
    fprintf(fp, "(%d", v[0]);
    for(int i = 1; i < 2;++i){
	fprintf(fp, " %d", v[i]);
    }
    fprintf(fp, ")\n");
}

int scan(FILE* fp, const ivec2& v)
{
    ivec2 v_cp = v;

    int a = fscanf(fp, " (");
    for(int i = 0; i < 2;++i){
	a += fscanf(fp, " %d", &v_cp[i]);
    }
    a += fscanf(fp, " )");
    return a;
}





const int ivec3::n = 3;




//| I/O
void print(const ivec3& a)
{
    LOG("(%d", a[0]);
    for(int i = 1; i < 3;++i){
	LOG(" %d", a[i]);
    }
    LOG(") ");
}

void store(FILE* fp, const ivec3& v)
{
    fprintf(fp, "(%d", v[0]);
    for(int i = 1; i < 3;++i){
	fprintf(fp, " %d", v[i]);
    }
    fprintf(fp, ")\n");
}

int scan(FILE* fp, const ivec3& v)
{
    ivec3 v_cp = v;

    int a = fscanf(fp, " (");
    for(int i = 0; i < 3;++i){
	a += fscanf(fp, " %d", &v_cp[i]);
    }
    a += fscanf(fp, " )");
    return a;
}





const int ivec4::n = 4;




//| I/O
void print(const ivec4& a)
{
    LOG("(%d", a[0]);
    for(int i = 1; i < 4;++i){
	LOG(" %d", a[i]);
    }
    LOG(") ");
}

void store(FILE* fp, const ivec4& v)
{
    fprintf(fp, "(%d", v[0]);
    for(int i = 1; i < 4;++i){
	fprintf(fp, " %d", v[i]);
    }
    fprintf(fp, ")\n");
}

int scan(FILE* fp, const ivec4& v)
{
    ivec4 v_cp = v;

    int a = fscanf(fp, " (");
    for(int i = 0; i < 4;++i){
	a += fscanf(fp, " %d", &v_cp[i]);
    }
    a += fscanf(fp, " )");
    return a;
}


}; //namespace graphics