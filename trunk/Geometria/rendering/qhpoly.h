#ifndef QHPOLY_H
#define QHPOLY_H

#include <QVector>
#include <QVector3D>

class QHPoly{
public:
  QHPoly();
  QHPoly(const int &v0, const int &v1, const int &v2, const QVector<QVector3D> *vs, const QHPoly *parent );
  QHPoly( const QHPoly &poly, const bool inverse );

  void CalcHull2D();

  QVector<int> face_v_;
  QVector3D n_;
  QVector3D c_;
  QVector<int> subset_v_;
  const QVector<QVector3D> *vs_;
};

#endif // QHPOLY_H
