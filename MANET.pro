#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T19:27:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MANET
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    algorithm.cpp \
    dijkstra.cpp \
    manet.cc \
    message.cpp \
    nodeitem.cpp \
    randomwalkmodel.cpp \
    street.cpp \
    streetwalkmodel.cpp \
    walkmodel.cpp \
    node.cpp \
    Eigen/src/Cholesky/CholeskyInstantiations.cpp \
    Eigen/src/Core/CoreInstantiations.cpp \
    Eigen/src/QR/QrInstantiations.cpp

HEADERS  += mainwindow.h \
    algorithm.h \
    dijkstra.h \
    manet.h \
    message.h \
    node.h \
    nodeitem.h \
    randomwalkmodel.h \
    street.h \
    streetwalkmodel.h \
    walkmodel.h \
    Eigen/src/Array/BooleanRedux.h \
    Eigen/src/Array/CwiseOperators.h \
    Eigen/src/Array/Functors.h \
    Eigen/src/Array/Norms.h \
    Eigen/src/Array/PartialRedux.h \
    Eigen/src/Array/Random.h \
    Eigen/src/Array/Select.h \
    Eigen/src/Cholesky/LDLT.h \
    Eigen/src/Cholesky/LLT.h \
    Eigen/src/Core/arch/AltiVec/PacketMath.h \
    Eigen/src/Core/arch/SSE/PacketMath.h \
    Eigen/src/Core/util/Constants.h \
    Eigen/src/Core/util/DisableMSVCWarnings.h \
    Eigen/src/Core/util/EnableMSVCWarnings.h \
    Eigen/src/Core/util/ForwardDeclarations.h \
    Eigen/src/Core/util/Macros.h \
    Eigen/src/Core/util/Memory.h \
    Eigen/src/Core/util/Meta.h \
    Eigen/src/Core/util/StaticAssert.h \
    Eigen/src/Core/util/XprHelper.h \
    Eigen/src/Core/Assign.h \
    Eigen/src/Core/Block.h \
    Eigen/src/Core/CacheFriendlyProduct.h \
    Eigen/src/Core/Coeffs.h \
    Eigen/src/Core/CommaInitializer.h \
    Eigen/src/Core/Cwise.h \
    Eigen/src/Core/CwiseBinaryOp.h \
    Eigen/src/Core/CwiseNullaryOp.h \
    Eigen/src/Core/CwiseUnaryOp.h \
    Eigen/src/Core/DiagonalCoeffs.h \
    Eigen/src/Core/DiagonalMatrix.h \
    Eigen/src/Core/DiagonalProduct.h \
    Eigen/src/Core/Dot.h \
    Eigen/src/Core/Flagged.h \
    Eigen/src/Core/Functors.h \
    Eigen/src/Core/Fuzzy.h \
    Eigen/src/Core/GenericPacketMath.h \
    Eigen/src/Core/IO.h \
    Eigen/src/Core/Map.h \
    Eigen/src/Core/MapBase.h \
    Eigen/src/Core/MathFunctions.h \
    Eigen/src/Core/Matrix.h \
    Eigen/src/Core/MatrixBase.h \
    Eigen/src/Core/MatrixStorage.h \
    Eigen/src/Core/Minor.h \
    Eigen/src/Core/NestByValue.h \
    Eigen/src/Core/NumTraits.h \
    Eigen/src/Core/Part.h \
    Eigen/src/Core/Product.h \
    Eigen/src/Core/Redux.h \
    Eigen/src/Core/SolveTriangular.h \
    Eigen/src/Core/Sum.h \
    Eigen/src/Core/Swap.h \
    Eigen/src/Core/Transpose.h \
    Eigen/src/Core/Visitor.h \
    Eigen/src/Geometry/AlignedBox.h \
    Eigen/src/Geometry/AngleAxis.h \
    Eigen/src/Geometry/EulerAngles.h \
    Eigen/src/Geometry/Hyperplane.h \
    Eigen/src/Geometry/OrthoMethods.h \
    Eigen/src/Geometry/ParametrizedLine.h \
    Eigen/src/Geometry/Quaternion.h \
    Eigen/src/Geometry/Rotation2D.h \
    Eigen/src/Geometry/RotationBase.h \
    Eigen/src/Geometry/Scaling.h \
    Eigen/src/Geometry/Transform.h \
    Eigen/src/Geometry/Translation.h \
    Eigen/src/LeastSquares/LeastSquares.h \
    Eigen/src/LU/Determinant.h \
    Eigen/src/LU/Inverse.h \
    Eigen/src/LU/LU.h \
    Eigen/src/QR/EigenSolver.h \
    Eigen/src/QR/HessenbergDecomposition.h \
    Eigen/src/QR/QR.h \
    Eigen/src/QR/SelfAdjointEigenSolver.h \
    Eigen/src/QR/Tridiagonalization.h \
    Eigen/src/Sparse/AmbiVector.h \
    Eigen/src/Sparse/CholmodSupport.h \
    Eigen/src/Sparse/CompressedStorage.h \
    Eigen/src/Sparse/CoreIterators.h \
    Eigen/src/Sparse/DynamicSparseMatrix.h \
    Eigen/src/Sparse/MappedSparseMatrix.h \
    Eigen/src/Sparse/RandomSetter.h \
    Eigen/src/Sparse/SparseAssign.h \
    Eigen/src/Sparse/SparseBlock.h \
    Eigen/src/Sparse/SparseCwise.h \
    Eigen/src/Sparse/SparseCwiseBinaryOp.h \
    Eigen/src/Sparse/SparseCwiseUnaryOp.h \
    Eigen/src/Sparse/SparseDiagonalProduct.h \
    Eigen/src/Sparse/SparseDot.h \
    Eigen/src/Sparse/SparseFlagged.h \
    Eigen/src/Sparse/SparseFuzzy.h \
    Eigen/src/Sparse/SparseLDLT.h \
    Eigen/src/Sparse/SparseLLT.h \
    Eigen/src/Sparse/SparseLU.h \
    Eigen/src/Sparse/SparseMatrix.h \
    Eigen/src/Sparse/SparseMatrixBase.h \
    Eigen/src/Sparse/SparseProduct.h \
    Eigen/src/Sparse/SparseRedux.h \
    Eigen/src/Sparse/SparseTranspose.h \
    Eigen/src/Sparse/SparseUtil.h \
    Eigen/src/Sparse/SparseVector.h \
    Eigen/src/Sparse/SuperLUSupport.h \
    Eigen/src/Sparse/TaucsSupport.h \
    Eigen/src/Sparse/TriangularSolver.h \
    Eigen/src/Sparse/UmfPackSupport.h \
    Eigen/src/SVD/SVD.h

FORMS    += mainwindow.ui

DISTFILES += \
    images/blue.png \\
    images/bus.png \
    images/green.png \
    images/grey.png \
    images/orange.png \
    images/red.png
