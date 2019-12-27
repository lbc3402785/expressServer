#pragma once

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

struct TriTraits : public OpenMesh::DefaultTraits
{
    typedef OpenMesh::Vec3f Point;
    typedef OpenMesh::Vec3f Normal;
    typedef OpenMesh::Vec2f TexCoord2D;
    typedef OpenMesh::Vec4uc Color;

    EdgeTraits {
        public:
        bool is_feature() const {
            return m_feature;
        }
        void set_feature(bool feature) {
            m_feature = feature;
        }
        private:
        bool m_feature = false;
    };
};
typedef OpenMesh::TriMesh_ArrayKernelT<TriTraits>  TriMesh;
typedef OpenMesh::PolyMesh_ArrayKernelT<TriTraits> PolyMesh;
