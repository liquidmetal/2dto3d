#include "writeply.h"
#include "ply.h"

writeply::writeply()
{
        //ctor
}

writeply::~writeply()
{
        //dtor
}

void write( ){
char *filename = "F:\\2DTO3D\\model.ply";
FILE* fp = fopen("F:\\2DTO3D\\model.ply","w+");
int nelems = 2;
char **elem_names = {"vertex","face"};
int file_type = PLY_ASCII;
PlyProperty vert_props[] = {
  {"x", Float32, Float32, offsetof(Vertex,x), 0, 0, 0, 0},
  {"y", Float32, Float32, offsetof(Vertex,y), 0, 0, 0, 0},
  {"z", Float32, Float32, offsetof(Vertex,z), 0, 0, 0, 0},
};

PlyProperty face_props[] = {
  {"vertex_indices",Uint8 , Int32, offsetof(Face,verts), 1, Uint8, Uint8,offsetof(Face,nverts)}
};
PlyFile *model =write_ply ( fp,  nelems, elem_names,  file_type );
if(model != NULL){
        model =open_for_writing_ply (filename,  nelems, elem_names,file_type );
        element_layout_ply ( model, elem_names[0], nelems, 3,vert_props );
        element_layout_ply ( model, elem_names[1], nelems, 1,face_props );

        ply_describe_property ( model, elem_names[0],  vert_props);
        ply_describe_property ( model, elem_names[1],  face_props);

        element_count_ply ( model, elem_names[0], 8);
        element_count_ply ( model, elem_names[1], 6);
        header_complete_ply(model);
}

else
        printf("Model file null");

}
