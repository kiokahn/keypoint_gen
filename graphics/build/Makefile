include source.txt
include cuda.txt
include cuda_out.txt
include qt_resource.txt
include qt_resource_out.txt

include qt_moc.txt
include qt_moc_out.txt

include qt_uic.txt
include qt_uic_out.txt
include obj.txt

BUILD_DIR = ../../../lib
OBJ_DIR := tmp

ARCH_RELATED = x86_64-linux-gnu

CFLAGS = -O3 -fPIC
CC = g++
DEFINES = -D LINUX
INCLUDES = -I../.. -I../../external_include/Eigen -I../../external_include/freetype \
-I../../external_include \
-I/usr/include/$(ARCH_RELATED)/qt5

TARGET = $(addprefix $(BUILD_DIR)/, libgraphics.a)

REBUILDABLES = $(OBJ) $(CUDA_OBJ) $(QT_MOC_OUT) $(QT_RESOURCE_OUT) $(QT_UIC_OUT)  $(TARGET)

clean:
	rm -f $(REBUILDABLES)

first: all

all:$(OBJ_DIR) $(TARGET)
	echo All done

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(QT_UIC_OUT) $(QT_RESOURCE_OUT) $(QT_MOC_OUT)  $(OBJ) $(CUDA_OBJ) 
	ar cqs $@ $(OBJ) $(CUDA_OBJ)

depend:
	makedepend -- $(INCLUDES) $(CFLAGS) -- $(SRC)
include compile.txt
include	qt_uic_compile.txt
include qt_resource_compile.txt
include qt_moc_compile.txt
include cuda_compile.txt
# DO NOT DELETE

../src/barycentric.o: ../../graphics/barycentric.h ../../graphics/vec.h
../src/barycentric.o: ../../graphics/real.h /usr/include/stdio.h
../src/barycentric.o: ../../graphics/ivec.h /usr/include/math.h
../src/barycentric.o: ../../graphics/epsilon.h ../../graphics/geom.h
../src/barycentric.o: ../../graphics/sys.h /usr/include/stdint.h
../src/barycentric.o: /usr/include/fcntl.h /usr/include/features.h
../src/barycentric.o: /usr/include/stdc-predef.h ../../graphics/vector.h
../src/barycentric.o: ../../graphics/log.h ../../graphics/misc.h
../src/barycentric.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/barycentric.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/barycentric.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/binomial.o: ../../graphics/binomial.h ../../graphics/sys.h
../src/binomial.o: /usr/include/stdint.h /usr/include/stdio.h
../src/binomial.o: /usr/include/fcntl.h /usr/include/features.h
../src/binomial.o: /usr/include/stdc-predef.h ../../graphics/log.h
../src/binomial.o: ../../graphics/ivec.h ../../graphics/vector.h
../src/binomial.o: ../../graphics/misc.h ../../graphics/real.h
../src/binomial.o: /usr/include/math.h ../../graphics/matrix.h
../src/binomial.o: ../../graphics/vec.h ../../graphics/epsilon.h
../src/binomial.o: ../../graphics/minmax.h
../src/bit_count.o: ../../graphics/bit_count.h
../src/camera.o: ../../graphics/camera.h ../../graphics/sys.h
../src/camera.o: /usr/include/stdint.h /usr/include/stdio.h
../src/camera.o: /usr/include/fcntl.h /usr/include/features.h
../src/camera.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/camera.o: ../../graphics/frame.h ../../graphics/vec.h
../src/camera.o: ../../graphics/ivec.h /usr/include/math.h
../src/camera.o: ../../graphics/epsilon.h ../../graphics/matrix.h
../src/camera.o: ../../graphics/log.h ../../graphics/vector.h
../src/camera.o: ../../graphics/misc.h ../../graphics/minmax.h
../src/camera.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/camera.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/camera.o: ../../graphics/gl.h ../../graphics/geom.h
../src/camera.o: ../../graphics/unsigned.h ../../graphics/color_buffer.h
../src/camera.o: ../../graphics/gl_stat.h ../../graphics/virtual_model.h
../src/camera.o: ../../graphics/CameraModeling.h ../../graphics/viewport.h
../src/camera.o: ../../graphics/color_buffer64.h ../../graphics/_limits.h
../src/camera.o: ../../external_include/GL/glext.h /usr/include/inttypes.h
../src/camera.o: ../../graphics/projector.h
../src/CameraInterface.o: ../../graphics/gl_extension.h ../../graphics/sys.h
../src/CameraInterface.o: /usr/include/stdint.h /usr/include/stdio.h
../src/CameraInterface.o: /usr/include/fcntl.h /usr/include/features.h
../src/CameraInterface.o: /usr/include/stdc-predef.h
../src/CameraInterface.o: ../../graphics/CameraInterface.h
../src/CameraInterface.o: ../../graphics/event.h ../../graphics/geom.h
../src/CameraInterface.o: ../../graphics/real.h ../../graphics/vec.h
../src/CameraInterface.o: ../../graphics/ivec.h /usr/include/math.h
../src/CameraInterface.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/CameraInterface.o: ../../graphics/log.h ../../graphics/misc.h
../src/CameraInterface.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/CameraInterface.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/CameraInterface.o: ../../graphics/EulerAngles.h
../src/CameraInterface.o: ../../graphics/QuatTypes.h
../src/CameraInterface.o: ../../graphics/keystate.h
../src/CameraInterface.o: ../../graphics/special_keys.h
../src/CameraInterface.o: ../../graphics/frame.h ../../graphics/gl.h
../src/CameraInterface.o: ../../graphics/unsigned.h
../src/CameraInterface.o: ../../graphics/color_buffer.h
../src/CameraInterface.o: ../../graphics/gl_stat.h ../../graphics/camera.h
../src/CameraInterface.o: ../../graphics/virtual_model.h
../src/CameraInterface.o: ../../graphics/CameraModeling.h
../src/CameraInterface.o: ../../graphics/viewport.h
../src/CameraInterface.o: ../../graphics/color_buffer64.h
../src/CameraInterface.o: ../../graphics/Viewer.h
../src/camera_map.o: ../../graphics/camera_map.h ../../graphics/camera.h
../src/camera_map.o: ../../graphics/sys.h /usr/include/stdint.h
../src/camera_map.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/camera_map.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/camera_map.o: ../../graphics/real.h ../../graphics/frame.h
../src/camera_map.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/camera_map.o: /usr/include/math.h ../../graphics/epsilon.h
../src/camera_map.o: ../../graphics/matrix.h ../../graphics/log.h
../src/camera_map.o: ../../graphics/vector.h ../../graphics/misc.h
../src/camera_map.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/camera_map.o: ../../graphics/matrix3x3.h ../../graphics/EulerAngles.h
../src/camera_map.o: ../../graphics/QuatTypes.h ../../graphics/gl.h
../src/camera_map.o: ../../graphics/geom.h ../../graphics/unsigned.h
../src/camera_map.o: ../../graphics/color_buffer.h ../../graphics/gl_stat.h
../src/camera_map.o: ../../graphics/virtual_model.h
../src/camera_map.o: ../../graphics/CameraModeling.h
../src/camera_map.o: ../../graphics/viewport.h
../src/camera_map.o: ../../graphics/color_buffer64.h ../../graphics/glInfo.h
../src/change_type.o: ../../graphics/change_type.h ../../graphics/vec.h
../src/change_type.o: ../../graphics/real.h /usr/include/stdio.h
../src/change_type.o: ../../graphics/ivec.h /usr/include/math.h
../src/change_type.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/change_type.o: ../../graphics/sys.h /usr/include/stdint.h
../src/change_type.o: /usr/include/fcntl.h /usr/include/features.h
../src/change_type.o: /usr/include/stdc-predef.h ../../graphics/log.h
../src/change_type.o: ../../graphics/misc.h
../src/cluster.o: ../../graphics/cluster.h /usr/include/assert.h
../src/cluster.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/color.o: ../../graphics/real.h ../../graphics/color.h
../src/color.o: ../../graphics/vec.h /usr/include/stdio.h
../src/color.o: ../../graphics/ivec.h /usr/include/math.h
../src/color.o: ../../graphics/epsilon.h ../../graphics/quater.h
../src/color.o: ../../graphics/sys.h /usr/include/stdint.h
../src/color.o: /usr/include/fcntl.h /usr/include/features.h
../src/color.o: /usr/include/stdc-predef.h ../../graphics/matrix3x3.h
../src/color.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/color_buffer.o: ../../graphics/color_buffer.h ../../graphics/sys.h
../src/color_buffer.o: /usr/include/stdint.h /usr/include/stdio.h
../src/color_buffer.o: /usr/include/fcntl.h /usr/include/features.h
../src/color_buffer.o: /usr/include/stdc-predef.h ../../graphics/unsigned.h
../src/color_buffer.o: ../../graphics/vector.h ../../graphics/log.h
../src/color_buffer.o: ../../graphics/misc.h ../../graphics/real.h
../src/color_buffer.o: /usr/include/math.h ../../graphics/ivec.h
../src/color_buffer.o: ../../graphics/gl_stat.h ../../graphics/geom.h
../src/color_buffer.o: ../../graphics/vec.h ../../graphics/epsilon.h
../src/color_buffer.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/color_buffer.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/color_buffer.o: ../../graphics/EulerAngles.h
../src/color_buffer.o: ../../graphics/QuatTypes.h
../src/color_buffer.o: ../../graphics/gl_extension.h
../src/color_buffer.o: ../../graphics/render_buffer.h ../../graphics/gl.h
../src/color_buffer64.o: ../../graphics/color_buffer64.h ../../graphics/sys.h
../src/color_buffer64.o: /usr/include/stdint.h /usr/include/stdio.h
../src/color_buffer64.o: /usr/include/fcntl.h /usr/include/features.h
../src/color_buffer64.o: /usr/include/stdc-predef.h ../../graphics/unsigned.h
../src/color_buffer64.o: ../../graphics/vector.h ../../graphics/log.h
../src/color_buffer64.o: ../../graphics/misc.h ../../graphics/real.h
../src/color_buffer64.o: /usr/include/math.h ../../graphics/ivec.h
../src/color_buffer64.o: ../../graphics/gl_stat.h ../../graphics/geom.h
../src/color_buffer64.o: ../../graphics/vec.h ../../graphics/epsilon.h
../src/color_buffer64.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/color_buffer64.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/color_buffer64.o: ../../graphics/EulerAngles.h
../src/color_buffer64.o: ../../graphics/QuatTypes.h
../src/color_buffer64.o: ../../graphics/gl_extension.h
../src/color_buffer64.o: ../../graphics/render_buffer.h ../../graphics/gl.h
../src/color_buffer64.o: ../../graphics/color_buffer.h
../src/ComputeShader.o: ../../graphics/ComputeShader.h ../../graphics/sys.h
../src/ComputeShader.o: /usr/include/stdint.h /usr/include/stdio.h
../src/ComputeShader.o: /usr/include/fcntl.h /usr/include/features.h
../src/ComputeShader.o: /usr/include/stdc-predef.h
../src/crop_ms.o: ../../graphics/crop_ms.h ../../graphics/sys.h
../src/crop_ms.o: /usr/include/stdint.h /usr/include/stdio.h
../src/crop_ms.o: /usr/include/fcntl.h /usr/include/features.h
../src/crop_ms.o: /usr/include/stdc-predef.h ../../graphics/Shader.h
../src/crop_ms.o: ../../graphics/ivec.h ../../graphics/vec.h
../src/crop_ms.o: ../../graphics/real.h /usr/include/math.h
../src/crop_ms.o: ../../graphics/epsilon.h ../../graphics/texture_buffer.h
../src/crop_ms.o: ../../graphics/gl.h ../../graphics/misc.h
../src/crop_ms.o: ../../graphics/geom.h ../../graphics/vector.h
../src/crop_ms.o: ../../graphics/log.h ../../graphics/matrix.h
../src/crop_ms.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/crop_ms.o: ../../graphics/matrix3x3.h ../../graphics/EulerAngles.h
../src/crop_ms.o: ../../graphics/QuatTypes.h ../../graphics/unsigned.h
../src/crop_ms.o: ../../graphics/color_buffer.h ../../graphics/gl_stat.h
../src/crop_ms.o: ../../graphics/gl_extension.h
../src/crop_ms.o: ../../graphics/texture_buffer_ms.h
../src/Delaunay.o: ../../graphics/Delaunay.h /usr/include/math.h
../src/Delaunay.o: ../../graphics/real.h ../../graphics/vec.h
../src/Delaunay.o: /usr/include/stdio.h ../../graphics/ivec.h
../src/Delaunay.o: ../../graphics/epsilon.h
../src/depth_texture_buffer.o: ../../graphics/depth_texture_buffer.h
../src/depth_texture_buffer.o: ../../graphics/sys.h /usr/include/stdint.h
../src/depth_texture_buffer.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/depth_texture_buffer.o: /usr/include/features.h
../src/depth_texture_buffer.o: /usr/include/stdc-predef.h ../../graphics/gl.h
../src/depth_texture_buffer.o: ../../graphics/real.h ../../graphics/vec.h
../src/depth_texture_buffer.o: ../../graphics/ivec.h /usr/include/math.h
../src/depth_texture_buffer.o: ../../graphics/epsilon.h ../../graphics/misc.h
../src/depth_texture_buffer.o: ../../graphics/geom.h ../../graphics/vector.h
../src/depth_texture_buffer.o: ../../graphics/log.h ../../graphics/matrix.h
../src/depth_texture_buffer.o: ../../graphics/minmax.h
../src/depth_texture_buffer.o: ../../graphics/quater.h
../src/depth_texture_buffer.o: ../../graphics/matrix3x3.h
../src/depth_texture_buffer.o: ../../graphics/EulerAngles.h
../src/depth_texture_buffer.o: ../../graphics/QuatTypes.h
../src/depth_texture_buffer.o: ../../graphics/unsigned.h
../src/depth_texture_buffer.o: ../../graphics/color_buffer.h
../src/depth_texture_buffer.o: ../../graphics/gl_stat.h
../src/depth_texture_buffer.o: ../../graphics/gl_extension.h
../src/depth_texture_buffer_ms.o: ../../graphics/depth_texture_buffer_ms.h
../src/depth_texture_buffer_ms.o: ../../graphics/sys.h /usr/include/stdint.h
../src/depth_texture_buffer_ms.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/depth_texture_buffer_ms.o: /usr/include/features.h
../src/depth_texture_buffer_ms.o: /usr/include/stdc-predef.h
../src/depth_texture_buffer_ms.o: ../../graphics/gl.h ../../graphics/real.h
../src/depth_texture_buffer_ms.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/depth_texture_buffer_ms.o: /usr/include/math.h
../src/depth_texture_buffer_ms.o: ../../graphics/epsilon.h
../src/depth_texture_buffer_ms.o: ../../graphics/misc.h ../../graphics/geom.h
../src/depth_texture_buffer_ms.o: ../../graphics/vector.h
../src/depth_texture_buffer_ms.o: ../../graphics/log.h
../src/depth_texture_buffer_ms.o: ../../graphics/matrix.h
../src/depth_texture_buffer_ms.o: ../../graphics/minmax.h
../src/depth_texture_buffer_ms.o: ../../graphics/quater.h
../src/depth_texture_buffer_ms.o: ../../graphics/matrix3x3.h
../src/depth_texture_buffer_ms.o: ../../graphics/EulerAngles.h
../src/depth_texture_buffer_ms.o: ../../graphics/QuatTypes.h
../src/depth_texture_buffer_ms.o: ../../graphics/unsigned.h
../src/depth_texture_buffer_ms.o: ../../graphics/color_buffer.h
../src/depth_texture_buffer_ms.o: ../../graphics/gl_stat.h
../src/depth_texture_buffer_ms.o: ../../graphics/gl_extension.h
../src/depth_texture_buffer_ms.o: ../../graphics/depth_texture_buffer.h
../src/displacement_map.o: ../../graphics/sys.h /usr/include/stdint.h
../src/displacement_map.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/displacement_map.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/displacement_map.o: ../../graphics/glInfo.h
../src/displacement_map.o: ../../graphics/gl_extension.h
../src/displacement_map.o: ../../graphics/displacement_map.h
../src/displacement_map.o: ../../graphics/Shader.h
../src/epsilon.o: ../../graphics/epsilon.h ../../graphics/real.h
../src/epsilon.o: /usr/include/math.h ../../graphics/sys.h
../src/epsilon.o: /usr/include/stdint.h /usr/include/stdio.h
../src/epsilon.o: /usr/include/fcntl.h /usr/include/features.h
../src/epsilon.o: /usr/include/stdc-predef.h
../src/EulerAngles.o: /usr/include/math.h ../../graphics/EulerAngles.h
../src/EulerAngles.o: ../../graphics/QuatTypes.h
../src/event.o: ../../graphics/event.h ../../graphics/geom.h
../src/event.o: ../../graphics/sys.h /usr/include/stdint.h
../src/event.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/event.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/event.o: ../../graphics/real.h ../../graphics/vec.h
../src/event.o: ../../graphics/ivec.h /usr/include/math.h
../src/event.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/event.o: ../../graphics/log.h ../../graphics/misc.h
../src/event.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/event.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/event.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/event.o: ../../graphics/keystate.h ../../graphics/special_keys.h
../src/fmatrix.o: ../../external_include/Eigen/Dense
../src/fmatrix.o: ../../external_include/Eigen/Core
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/DisableStupidWarnings.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/Macros.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/MKL_support.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/Constants.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/Meta.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/ForwardDeclarations.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/StaticAssert.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/XprHelper.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/Memory.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/NumTraits.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/MathFunctions.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/GenericPacketMath.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/MathFunctionsImpl.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/arch/CUDA/Half.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/arch/CUDA/PacketMathHalf.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/arch/CUDA/TypeCasting.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/arch/Default/Settings.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/functors/TernaryFunctors.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/functors/BinaryFunctors.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/functors/UnaryFunctors.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/functors/NullaryFunctors.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/functors/StlFunctors.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/functors/AssignmentFunctors.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/arch/CUDA/Complex.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/IO.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/DenseCoeffsBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/DenseBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/plugins/BlockMethods.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/MatrixBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/plugins/CommonCwiseUnaryOps.h
../src/fmatrix.o: ../../external_include/Eigen/src/plugins/CommonCwiseBinaryOps.h
../src/fmatrix.o: ../../external_include/Eigen/src/plugins/MatrixCwiseUnaryOps.h
../src/fmatrix.o: ../../external_include/Eigen/src/plugins/MatrixCwiseBinaryOps.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/EigenBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Product.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CoreEvaluators.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/AssignEvaluator.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Assign.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/ArrayBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/plugins/ArrayCwiseUnaryOps.h
../src/fmatrix.o: ../../external_include/Eigen/src/plugins/ArrayCwiseBinaryOps.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/BlasUtil.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/DenseStorage.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/NestByValue.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/ReturnByValue.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/NoAlias.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/PlainObjectBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Matrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Array.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CwiseTernaryOp.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CwiseBinaryOp.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CwiseUnaryOp.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CwiseNullaryOp.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CwiseUnaryView.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/SelfCwiseBinaryOp.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Dot.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/StableNorm.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Stride.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/MapBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Map.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Ref.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Block.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/VectorBlock.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Transpose.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/DiagonalMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Diagonal.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/DiagonalProduct.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Redux.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Visitor.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Fuzzy.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Swap.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CommaInitializer.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/GeneralProduct.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Solve.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Inverse.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/SolverBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/PermutationMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Transpositions.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/TriangularMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/SelfAdjointView.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/GeneralBlockPanelKernel.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/Parallelizer.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/ProductEvaluators.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/GeneralMatrixVector.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/GeneralMatrixMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/SolveTriangular.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/SelfadjointMatrixVector.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/SelfadjointMatrixMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/SelfadjointProduct.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/SelfadjointRank2Update.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/TriangularMatrixVector.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/TriangularMatrixMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/TriangularSolverMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/products/TriangularSolverVector.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/BandMatrix.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/CoreIterators.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/ConditionEstimator.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/BooleanRedux.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Select.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/VectorwiseOp.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Random.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Replicate.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/Reverse.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/ArrayWrapper.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/GlobalFunctions.h
../src/fmatrix.o: ../../external_include/Eigen/src/Core/util/ReenableStupidWarnings.h
../src/fmatrix.o: ../../external_include/Eigen/LU
../src/fmatrix.o: ../../external_include/Eigen/src/misc/Kernel.h
../src/fmatrix.o: ../../external_include/Eigen/src/misc/Image.h
../src/fmatrix.o: ../../external_include/Eigen/src/LU/FullPivLU.h
../src/fmatrix.o: ../../external_include/Eigen/src/LU/PartialPivLU.h
../src/fmatrix.o: ../../external_include/Eigen/src/LU/Determinant.h
../src/fmatrix.o: ../../external_include/Eigen/src/LU/InverseImpl.h
../src/fmatrix.o: ../../external_include/Eigen/Cholesky
../src/fmatrix.o: ../../external_include/Eigen/src/Cholesky/LLT.h
../src/fmatrix.o: ../../external_include/Eigen/src/Cholesky/LDLT.h
../src/fmatrix.o: ../../external_include/Eigen/QR
../src/fmatrix.o: ../../external_include/Eigen/Jacobi
../src/fmatrix.o: ../../external_include/Eigen/src/Jacobi/Jacobi.h
../src/fmatrix.o: ../../external_include/Eigen/Householder
../src/fmatrix.o: ../../external_include/Eigen/src/Householder/Householder.h
../src/fmatrix.o: ../../external_include/Eigen/src/Householder/HouseholderSequence.h
../src/fmatrix.o: ../../external_include/Eigen/src/Householder/BlockHouseholder.h
../src/fmatrix.o: ../../external_include/Eigen/src/QR/HouseholderQR.h
../src/fmatrix.o: ../../external_include/Eigen/src/QR/FullPivHouseholderQR.h
../src/fmatrix.o: ../../external_include/Eigen/src/QR/ColPivHouseholderQR.h
../src/fmatrix.o: ../../external_include/Eigen/src/QR/CompleteOrthogonalDecomposition.h
../src/fmatrix.o: ../../external_include/Eigen/SVD
../src/fmatrix.o: ../../external_include/Eigen/src/misc/RealSvd2x2.h
../src/fmatrix.o: ../../external_include/Eigen/src/SVD/UpperBidiagonalization.h
../src/fmatrix.o: ../../external_include/Eigen/src/SVD/SVDBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/SVD/JacobiSVD.h
../src/fmatrix.o: ../../external_include/Eigen/src/SVD/BDCSVD.h
../src/fmatrix.o: ../../external_include/Eigen/Geometry
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/OrthoMethods.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/EulerAngles.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Homogeneous.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/RotationBase.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Rotation2D.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Quaternion.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/AngleAxis.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Transform.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Translation.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Scaling.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Hyperplane.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/ParametrizedLine.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/AlignedBox.h
../src/fmatrix.o: ../../external_include/Eigen/src/Geometry/Umeyama.h
../src/fmatrix.o: ../../external_include/Eigen/Eigenvalues
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/Tridiagonalization.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/RealSchur.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/./HessenbergDecomposition.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/EigenSolver.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/./RealSchur.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/./Tridiagonalization.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/HessenbergDecomposition.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/ComplexSchur.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/ComplexEigenSolver.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/./ComplexSchur.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/RealQZ.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/./RealQZ.h
../src/fmatrix.o: ../../external_include/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h
../src/fmatrix.o: ../../graphics/fmatrix.h ../../graphics/real.h
../src/fmatrix.o: ../../graphics/sys.h /usr/include/stdint.h
../src/fmatrix.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/fmatrix.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/fmatrix.o: /usr/include/math.h ../../graphics/misc.h
../src/fmatrix.o: ../../graphics/log.h ../../graphics/minmax.h
../src/fmatrix.o: ../../graphics/matrix3x3.h ../../graphics/vec.h
../src/fmatrix.o: ../../graphics/ivec.h ../../graphics/epsilon.h
../src/fmatrix.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/fmatrix.o: ../../graphics/matrix3x4.h ../../graphics/matrix4x4.h
../src/frame.o: ../../graphics/frame.h ../../graphics/sys.h
../src/frame.o: /usr/include/stdint.h /usr/include/stdio.h
../src/frame.o: /usr/include/fcntl.h /usr/include/features.h
../src/frame.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/frame.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/frame.o: /usr/include/math.h ../../graphics/epsilon.h
../src/frame.o: ../../graphics/matrix.h ../../graphics/log.h
../src/frame.o: ../../graphics/vector.h ../../graphics/misc.h
../src/frame.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/frame.o: ../../graphics/matrix3x3.h ../../graphics/EulerAngles.h
../src/frame.o: ../../graphics/QuatTypes.h ../../graphics/gl.h
../src/frame.o: ../../graphics/geom.h ../../graphics/unsigned.h
../src/frame.o: ../../graphics/color_buffer.h ../../graphics/gl_stat.h
../src/frame.o: ../../graphics/change_type.h ../../graphics/_limits.h
../src/FrustumCulling.o: ../../graphics/FrustumCulling.h ../../graphics/sys.h
../src/FrustumCulling.o: /usr/include/stdint.h /usr/include/stdio.h
../src/FrustumCulling.o: /usr/include/fcntl.h /usr/include/features.h
../src/FrustumCulling.o: /usr/include/stdc-predef.h /usr/include/math.h
../src/gauss_dist_im.o: ../../graphics/gauss_dist_im.h ../../graphics/vec.h
../src/gauss_dist_im.o: ../../graphics/real.h /usr/include/stdio.h
../src/gauss_dist_im.o: ../../graphics/ivec.h /usr/include/math.h
../src/gauss_dist_im.o: ../../graphics/epsilon.h
../src/geom.o: ../../graphics/geom.h ../../graphics/sys.h
../src/geom.o: /usr/include/stdint.h /usr/include/stdio.h
../src/geom.o: /usr/include/fcntl.h /usr/include/features.h
../src/geom.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/geom.o: ../../graphics/vec.h ../../graphics/ivec.h /usr/include/math.h
../src/geom.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/geom.o: ../../graphics/log.h ../../graphics/misc.h
../src/geom.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/geom.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/geom.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/geom.o: ../../graphics/_limits.h ../../graphics/fmatrix.h
../src/geom.o: ../../graphics/matrix3x4.h ../../graphics/matrix4x4.h
../src/gHash.o: ../../graphics/gHash.h ../../graphics/real.h
../src/gHash.o: /usr/include/stdlib.h /usr/include/stdint.h
../src/gHash.o: /usr/include/string.h /usr/include/byteswap.h
../src/gHash.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/gl.o: ../../graphics/gl.h ../../graphics/sys.h /usr/include/stdint.h
../src/gl.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/gl.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/gl.o: ../../graphics/real.h ../../graphics/vec.h ../../graphics/ivec.h
../src/gl.o: /usr/include/math.h ../../graphics/epsilon.h
../src/gl.o: ../../graphics/misc.h ../../graphics/geom.h
../src/gl.o: ../../graphics/vector.h ../../graphics/log.h
../src/gl.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/gl.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/gl.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/gl.o: ../../graphics/unsigned.h ../../graphics/color_buffer.h
../src/gl.o: ../../graphics/gl_stat.h ../../graphics/frame.h
../src/gl.o: ../../graphics/camera.h ../../graphics/virtual_model.h
../src/gl.o: ../../graphics/CameraModeling.h ../../graphics/viewport.h
../src/gl.o: ../../graphics/color_buffer64.h
../src/glInfo.o: ../../graphics/glInfo.h
../src/glMultiGpu.o: ../../graphics/glMultiGpu.h
../src/gl_draw.o: ../../graphics/gl_draw.h ../../graphics/sys.h
../src/gl_draw.o: /usr/include/stdint.h /usr/include/stdio.h
../src/gl_draw.o: /usr/include/fcntl.h /usr/include/features.h
../src/gl_draw.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/gl_draw.o: ../../graphics/quater.h ../../graphics/vec.h
../src/gl_draw.o: ../../graphics/ivec.h /usr/include/math.h
../src/gl_draw.o: ../../graphics/epsilon.h ../../graphics/matrix3x3.h
../src/gl_draw.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/gl_draw.o: ../../graphics/misc.h ../../graphics/gl.h
../src/gl_draw.o: ../../graphics/geom.h ../../graphics/vector.h
../src/gl_draw.o: ../../graphics/log.h ../../graphics/matrix.h
../src/gl_draw.o: ../../graphics/minmax.h ../../graphics/unsigned.h
../src/gl_draw.o: ../../graphics/color_buffer.h ../../graphics/gl_stat.h
../src/gl_draw.o: ../../graphics/frame.h ../../graphics/camera.h
../src/gl_draw.o: ../../graphics/virtual_model.h
../src/gl_draw.o: ../../graphics/CameraModeling.h ../../graphics/viewport.h
../src/gl_draw.o: ../../graphics/color_buffer64.h
../src/gl_extension.o: ../../graphics/gl_extension.h ../../graphics/sys.h
../src/gl_extension.o: /usr/include/stdint.h /usr/include/stdio.h
../src/gl_extension.o: /usr/include/fcntl.h /usr/include/features.h
../src/gl_extension.o: /usr/include/stdc-predef.h
../src/gl_stat.o: ../../graphics/gl_stat.h ../../graphics/sys.h
../src/gl_stat.o: /usr/include/stdint.h /usr/include/stdio.h
../src/gl_stat.o: /usr/include/fcntl.h /usr/include/features.h
../src/gl_stat.o: /usr/include/stdc-predef.h
../src/gl_stat.o: ../../external_include/GL/glext.h /usr/include/inttypes.h
../src/gmatrix.o: ../../graphics/gmatrix.h ../../graphics/sys.h
../src/gmatrix.o: /usr/include/stdint.h /usr/include/stdio.h
../src/gmatrix.o: /usr/include/fcntl.h /usr/include/features.h
../src/gmatrix.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/gmatrix.o: ../../graphics/log.h ../../graphics/vec.h
../src/gmatrix.o: ../../graphics/ivec.h /usr/include/math.h
../src/gmatrix.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/gmatrix.o: ../../graphics/misc.h ../../graphics/matrix.h
../src/gmatrix.o: ../../graphics/minmax.h
../src/heap.o: ../../graphics/heap.h ../../graphics/sys.h
../src/heap.o: /usr/include/stdint.h /usr/include/stdio.h
../src/heap.o: /usr/include/fcntl.h /usr/include/features.h
../src/heap.o: /usr/include/stdc-predef.h ../../graphics/vector.h
../src/heap.o: ../../graphics/log.h ../../graphics/misc.h
../src/heap.o: ../../graphics/real.h /usr/include/math.h
../src/homography.o: ../../graphics/homography.h ../../graphics/vec.h
../src/homography.o: ../../graphics/real.h /usr/include/stdio.h
../src/homography.o: ../../graphics/ivec.h /usr/include/math.h
../src/homography.o: ../../graphics/epsilon.h ../../graphics/barycentric.h
../src/homography.o: ../../graphics/geom.h ../../graphics/sys.h
../src/homography.o: /usr/include/stdint.h /usr/include/fcntl.h
../src/homography.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/homography.o: ../../graphics/vector.h ../../graphics/log.h
../src/homography.o: ../../graphics/misc.h ../../graphics/matrix.h
../src/homography.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/homography.o: ../../graphics/matrix3x3.h ../../graphics/EulerAngles.h
../src/homography.o: ../../graphics/QuatTypes.h ../../graphics/gmatrix.h
../src/homography.o: ../../graphics/matrix_math.h ../../graphics/matrix.h
../src/image_sample.o: ../../graphics/image_sample.h ../../graphics/vec.h
../src/image_sample.o: ../../graphics/real.h /usr/include/stdio.h
../src/image_sample.o: ../../graphics/ivec.h /usr/include/math.h
../src/image_sample.o: ../../graphics/epsilon.h
../src/intersection.o: ../../graphics/intersection.h ../../graphics/frame.h
../src/intersection.o: ../../graphics/sys.h /usr/include/stdint.h
../src/intersection.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/intersection.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/intersection.o: ../../graphics/real.h ../../graphics/vec.h
../src/intersection.o: ../../graphics/ivec.h /usr/include/math.h
../src/intersection.o: ../../graphics/epsilon.h ../../graphics/matrix.h
../src/intersection.o: ../../graphics/log.h ../../graphics/vector.h
../src/intersection.o: ../../graphics/misc.h ../../graphics/minmax.h
../src/intersection.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/intersection.o: ../../graphics/EulerAngles.h
../src/intersection.o: ../../graphics/QuatTypes.h ../../graphics/gl.h
../src/intersection.o: ../../graphics/geom.h ../../graphics/unsigned.h
../src/intersection.o: ../../graphics/color_buffer.h ../../graphics/gl_stat.h
../src/interval.o: ../../graphics/interval.h ../../graphics/sys.h
../src/interval.o: /usr/include/stdint.h /usr/include/stdio.h
../src/interval.o: /usr/include/fcntl.h /usr/include/features.h
../src/interval.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/interval.o: /usr/include/math.h ../../graphics/epsilon.h
../src/interval.o: ../../graphics/log.h ../../graphics/minmax.h
../src/ivec.o: ../../graphics/ivec.h /usr/include/stdio.h
../src/ivec.o: ../../graphics/sys.h /usr/include/stdint.h
../src/ivec.o: /usr/include/fcntl.h /usr/include/features.h
../src/ivec.o: /usr/include/stdc-predef.h
../src/keystate.o: ../../graphics/keystate.h
../src/log.o: ../../graphics/log.h ../../graphics/sys.h /usr/include/stdint.h
../src/log.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/log.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/log.o: /usr/include/stdlib.h
../src/lu_decomp.o: /usr/include/math.h /usr/include/string.h
../src/Material_Shader.o: ../../graphics/sys.h /usr/include/stdint.h
../src/Material_Shader.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/Material_Shader.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/Material_Shader.o: ../../graphics/glInfo.h
../src/Material_Shader.o: ../../graphics/gl_extension.h
../src/Material_Shader.o: ../../graphics/Material_Shader.h
../src/Material_Shader.o: ../../graphics/vec.h ../../graphics/real.h
../src/Material_Shader.o: ../../graphics/ivec.h /usr/include/math.h
../src/Material_Shader.o: ../../graphics/epsilon.h ../../graphics/Shader.h
../src/matrix.o: ../../graphics/matrix.h ../../graphics/sys.h
../src/matrix.o: /usr/include/stdint.h /usr/include/stdio.h
../src/matrix.o: /usr/include/fcntl.h /usr/include/features.h
../src/matrix.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/matrix.o: /usr/include/math.h ../../graphics/log.h
../src/matrix.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/matrix.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/matrix.o: ../../graphics/misc.h ../../graphics/minmax.h
../src/matrix3x3.o: ../../graphics/matrix3x3.h ../../graphics/real.h
../src/matrix3x3.o: ../../graphics/sys.h /usr/include/stdint.h
../src/matrix3x3.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/matrix3x3.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/matrix3x3.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/matrix3x3.o: /usr/include/math.h ../../graphics/epsilon.h
../src/matrix3x3.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/matrix3x3.o: ../../graphics/matrix3x4.h
../src/matrix3x4.o: ../../graphics/matrix3x4.h ../../graphics/real.h
../src/matrix3x4.o: ../../graphics/sys.h /usr/include/stdint.h
../src/matrix3x4.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/matrix3x4.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/matrix3x4.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/matrix3x4.o: /usr/include/math.h ../../graphics/epsilon.h
../src/matrix3x4.o: ../../graphics/matrix3x3.h ../../graphics/EulerAngles.h
../src/matrix3x4.o: ../../graphics/QuatTypes.h
../src/matrix4x4.o: ../../graphics/matrix4x4.h ../../graphics/real.h
../src/matrix4x4.o: ../../graphics/sys.h /usr/include/stdint.h
../src/matrix4x4.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/matrix4x4.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/matrix4x4.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/matrix4x4.o: /usr/include/math.h ../../graphics/epsilon.h
../src/matrix4x4.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/matrix_math.o: ../../graphics/matrix_math.h ../../graphics/matrix.h
../src/minmax.o: ../../graphics/minmax.h ../../graphics/sys.h
../src/minmax.o: /usr/include/stdint.h /usr/include/stdio.h
../src/minmax.o: /usr/include/fcntl.h /usr/include/features.h
../src/minmax.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/misc.o: ../../graphics/misc.h ../../graphics/sys.h
../src/misc.o: /usr/include/stdint.h /usr/include/stdio.h
../src/misc.o: /usr/include/fcntl.h /usr/include/features.h
../src/misc.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/misc.o: /usr/include/math.h
../src/noise_api.o: ../../graphics/noise_api.h ../../graphics/sys.h
../src/noise_api.o: /usr/include/stdint.h /usr/include/stdio.h
../src/noise_api.o: /usr/include/fcntl.h /usr/include/features.h
../src/noise_api.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/noise_api.o: ../../graphics/src/noise_table.h /usr/include/math.h
../src/ogl_image_load.o: ../../graphics/ogl_image_load.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/QImage
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qimage.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtguiglobal.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qglobal.h
../src/ogl_image_load.o: /usr/include/assert.h /usr/include/features.h
../src/ogl_image_load.o: /usr/include/stdc-predef.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qconfig.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qtcore-config.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qsystemdetection.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qprocessordetection.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qcompilerdetection.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtgui-config.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qcolor.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qrgb.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qnamespace.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringlist.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qlist.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qalgorithms.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qiterator.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qrefcount.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qatomic.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qbasicatomic.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qarraydata.h
../src/ogl_image_load.o: /usr/include/string.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qhashfunctions.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstring.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qchar.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qbytearray.h
../src/ogl_image_load.o: /usr/include/stdlib.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringliteral.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringalgorithms.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringview.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qpair.h
../src/ogl_image_load.o: /usr/include/limits.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qbytearraylist.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qregexp.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringmatcher.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qrgba64.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpaintdevice.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qwindowdefs.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobjectdefs.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobjectdefs_impl.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qrect.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qmargins.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qsize.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qpoint.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpixelformat.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtransform.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qmatrix.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpolygon.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qvector.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qregion.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qdatastream.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qscopedpointer.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qiodevice.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobject.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qmetatype.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qvarlengtharray.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qcontainerfwd.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobject_impl.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qline.h
../src/ogl_image_load.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpainterpath.h
../src/ogl_image_load.o: ../../graphics/gl.h ../../graphics/sys.h
../src/ogl_image_load.o: /usr/include/stdint.h /usr/include/stdio.h
../src/ogl_image_load.o: /usr/include/fcntl.h ../../graphics/real.h
../src/ogl_image_load.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/ogl_image_load.o: /usr/include/math.h ../../graphics/epsilon.h
../src/ogl_image_load.o: ../../graphics/misc.h ../../graphics/geom.h
../src/ogl_image_load.o: ../../graphics/vector.h ../../graphics/log.h
../src/ogl_image_load.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/ogl_image_load.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/ogl_image_load.o: ../../graphics/EulerAngles.h
../src/ogl_image_load.o: ../../graphics/QuatTypes.h ../../graphics/unsigned.h
../src/ogl_image_load.o: ../../graphics/color_buffer.h
../src/ogl_image_load.o: ../../graphics/gl_stat.h
../src/parametrize.o: ../../graphics/parametrize.h ../../graphics/sys.h
../src/parametrize.o: /usr/include/stdint.h /usr/include/stdio.h
../src/parametrize.o: /usr/include/fcntl.h /usr/include/features.h
../src/parametrize.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/parametrize.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/parametrize.o: /usr/include/math.h ../../graphics/epsilon.h
../src/parametrize.o: ../../graphics/vector.h ../../graphics/log.h
../src/parametrize.o: ../../graphics/misc.h
../src/PixelBufferObj.o: ../../graphics/gl_extension.h ../../graphics/sys.h
../src/PixelBufferObj.o: /usr/include/stdint.h /usr/include/stdio.h
../src/PixelBufferObj.o: /usr/include/fcntl.h /usr/include/features.h
../src/PixelBufferObj.o: /usr/include/stdc-predef.h
../src/PixelBufferObj.o: ../../graphics/PixelBufferObj.h
../src/PixelBufferObj.o: ../../graphics/unsigned.h
../src/ply_reader.o: ../../graphics/ply_reader.h /usr/include/stdint.h
../src/ply_reader.o: ../../graphics/vec.h ../../graphics/real.h
../src/ply_reader.o: /usr/include/stdio.h ../../graphics/ivec.h
../src/ply_reader.o: /usr/include/math.h ../../graphics/epsilon.h
../src/pqueue.o: ../../graphics/pqueue.h ../../graphics/sys.h
../src/pqueue.o: /usr/include/stdint.h /usr/include/stdio.h
../src/pqueue.o: /usr/include/fcntl.h /usr/include/features.h
../src/pqueue.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/pqueue.o: ../../graphics/_limits.h
../src/projector.o: ../../graphics/projector.h ../../graphics/sys.h
../src/projector.o: /usr/include/stdint.h /usr/include/stdio.h
../src/projector.o: /usr/include/fcntl.h /usr/include/features.h
../src/projector.o: /usr/include/stdc-predef.h ../../graphics/quater.h
../src/projector.o: ../../graphics/real.h ../../graphics/vec.h
../src/projector.o: ../../graphics/ivec.h /usr/include/math.h
../src/projector.o: ../../graphics/epsilon.h ../../graphics/matrix3x3.h
../src/projector.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/projector.o: ../../graphics/geom.h ../../graphics/vector.h
../src/projector.o: ../../graphics/log.h ../../graphics/misc.h
../src/projector.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/projector.o: ../../graphics/gl.h ../../graphics/unsigned.h
../src/projector.o: ../../graphics/color_buffer.h ../../graphics/gl_stat.h
../src/projector.o: ../../graphics/camera.h ../../graphics/frame.h
../src/projector.o: ../../graphics/virtual_model.h
../src/projector.o: ../../graphics/CameraModeling.h ../../graphics/viewport.h
../src/projector.o: ../../graphics/color_buffer64.h
../src/QR.o: ../../graphics/QR.h ../../graphics/sys.h /usr/include/stdint.h
../src/QR.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/QR.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/QR.o: ../../graphics/real.h ../../graphics/matrix.h
../src/QR.o: /usr/include/math.h ../../graphics/log.h ../../graphics/vec.h
../src/QR.o: ../../graphics/ivec.h ../../graphics/epsilon.h
../src/QR.o: ../../graphics/vector.h ../../graphics/misc.h
../src/QR.o: ../../graphics/minmax.h
../src/quater.o: ../../graphics/quater.h ../../graphics/sys.h
../src/quater.o: /usr/include/stdint.h /usr/include/stdio.h
../src/quater.o: /usr/include/fcntl.h /usr/include/features.h
../src/quater.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/quater.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/quater.o: /usr/include/math.h ../../graphics/epsilon.h
../src/quater.o: ../../graphics/matrix3x3.h ../../graphics/EulerAngles.h
../src/quater.o: ../../graphics/QuatTypes.h
../src/quater_param.o: ../../graphics/quater_param.h ../../graphics/quater.h
../src/quater_param.o: ../../graphics/sys.h /usr/include/stdint.h
../src/quater_param.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/quater_param.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/quater_param.o: ../../graphics/real.h ../../graphics/vec.h
../src/quater_param.o: ../../graphics/ivec.h /usr/include/math.h
../src/quater_param.o: ../../graphics/epsilon.h ../../graphics/matrix3x3.h
../src/quater_param.o: ../../graphics/EulerAngles.h
../src/quater_param.o: ../../graphics/QuatTypes.h
../src/quater_param.o: ../../graphics/matrix_math.h ../../graphics/matrix.h
../src/rasterizer.o: ../../graphics/rasterizer.h ../../graphics/sys.h
../src/rasterizer.o: /usr/include/stdint.h /usr/include/stdio.h
../src/rasterizer.o: /usr/include/fcntl.h /usr/include/features.h
../src/rasterizer.o: /usr/include/stdc-predef.h ../../graphics/geom.h
../src/rasterizer.o: ../../graphics/real.h ../../graphics/vec.h
../src/rasterizer.o: ../../graphics/ivec.h /usr/include/math.h
../src/rasterizer.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/rasterizer.o: ../../graphics/log.h ../../graphics/misc.h
../src/rasterizer.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/rasterizer.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/rasterizer.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/real.o: ../../graphics/real.h
../src/render_alpha.o: ../../graphics/render_alpha.h ../../graphics/Shader.h
../src/render_alpha.o: ../../graphics/sys.h /usr/include/stdint.h
../src/render_alpha.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/render_alpha.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/render_alpha_bar.o: ../../graphics/render_alpha_bar.h
../src/render_alpha_bar.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_alpha_bar.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_alpha_bar.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_alpha_bar.o: /usr/include/stdc-predef.h
../src/render_bezier.o: ../../graphics/render_bezier.h
../src/render_bezier.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_bezier.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_bezier.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_bezier.o: /usr/include/stdc-predef.h ../../graphics/vec.h
../src/render_bezier.o: ../../graphics/real.h ../../graphics/ivec.h
../src/render_bezier.o: /usr/include/math.h ../../graphics/epsilon.h
../src/render_bezier_join.o: ../../graphics/render_bezier_join.h
../src/render_bezier_join.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_bezier_join.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_bezier_join.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_bezier_join.o: /usr/include/stdc-predef.h ../../graphics/vec.h
../src/render_bezier_join.o: ../../graphics/real.h ../../graphics/ivec.h
../src/render_bezier_join.o: /usr/include/math.h ../../graphics/epsilon.h
../src/render_bezier_path.o: ../../graphics/render_bezier_path.h
../src/render_bezier_path.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_bezier_path.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_bezier_path.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_bezier_path.o: /usr/include/stdc-predef.h
../src/render_buffer.o: ../../graphics/render_buffer.h ../../graphics/sys.h
../src/render_buffer.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_buffer.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_buffer.o: /usr/include/stdc-predef.h ../../graphics/gl.h
../src/render_buffer.o: ../../graphics/real.h ../../graphics/vec.h
../src/render_buffer.o: ../../graphics/ivec.h /usr/include/math.h
../src/render_buffer.o: ../../graphics/epsilon.h ../../graphics/misc.h
../src/render_buffer.o: ../../graphics/geom.h ../../graphics/vector.h
../src/render_buffer.o: ../../graphics/log.h ../../graphics/matrix.h
../src/render_buffer.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/render_buffer.o: ../../graphics/matrix3x3.h
../src/render_buffer.o: ../../graphics/EulerAngles.h
../src/render_buffer.o: ../../graphics/QuatTypes.h ../../graphics/unsigned.h
../src/render_buffer.o: ../../graphics/color_buffer.h
../src/render_buffer.o: ../../graphics/gl_stat.h
../src/render_buffer.o: ../../graphics/gl_extension.h
../src/render_homography.o: ../../graphics/render_homography.h
../src/render_homography.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_homography.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_homography.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_homography.o: /usr/include/stdc-predef.h
../src/render_homography.o: ../../graphics/homography.h ../../graphics/vec.h
../src/render_homography.o: ../../graphics/real.h ../../graphics/ivec.h
../src/render_homography.o: /usr/include/math.h ../../graphics/epsilon.h
../src/render_hsv.o: ../../graphics/render_hsv.h ../../graphics/Shader.h
../src/render_hsv.o: ../../graphics/sys.h /usr/include/stdint.h
../src/render_hsv.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/render_hsv.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/render_hsv_bar.o: ../../graphics/render_hsv_bar.h
../src/render_hsv_bar.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_hsv_bar.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_hsv_bar.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_hsv_bar.o: /usr/include/stdc-predef.h
../src/render_legend.o: ../../graphics/render_legend.h
../src/render_legend.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_legend.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_legend.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_legend.o: /usr/include/stdc-predef.h
../src/render_legend_bw.o: ../../graphics/render_legend_bw.h
../src/render_legend_bw.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_legend_bw.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_legend_bw.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_legend_bw.o: /usr/include/stdc-predef.h
../src/render_line.o: ../../graphics/render_line.h ../../graphics/Shader.h
../src/render_line.o: ../../graphics/sys.h /usr/include/stdint.h
../src/render_line.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/render_line.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/render_line.o: ../../graphics/vec.h ../../graphics/real.h
../src/render_line.o: ../../graphics/ivec.h /usr/include/math.h
../src/render_line.o: ../../graphics/epsilon.h
../src/render_normal.o: ../../graphics/render_normal.h
../src/render_normal.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_normal.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_normal.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_normal.o: /usr/include/stdc-predef.h
../src/render_normal_color.o: ../../graphics/render_normal_color.h
../src/render_normal_color.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_normal_color.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_normal_color.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_normal_color.o: /usr/include/stdc-predef.h
../src/render_path.o: ../../graphics/render_path.h ../../graphics/Shader.h
../src/render_path.o: ../../graphics/sys.h /usr/include/stdint.h
../src/render_path.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/render_path.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/render_scalar.o: ../../graphics/render_scalar.h
../src/render_scalar.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_scalar.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_scalar.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_scalar.o: /usr/include/stdc-predef.h
../src/render_scalar_bw.o: ../../graphics/render_scalar_bw.h
../src/render_scalar_bw.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/render_scalar_bw.o: /usr/include/stdint.h /usr/include/stdio.h
../src/render_scalar_bw.o: /usr/include/fcntl.h /usr/include/features.h
../src/render_scalar_bw.o: /usr/include/stdc-predef.h
../src/scaled_frame.o: ../../graphics/scaled_frame.h ../../graphics/sys.h
../src/scaled_frame.o: /usr/include/stdint.h /usr/include/stdio.h
../src/scaled_frame.o: /usr/include/fcntl.h /usr/include/features.h
../src/scaled_frame.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/scaled_frame.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/scaled_frame.o: /usr/include/math.h ../../graphics/epsilon.h
../src/scaled_frame.o: ../../graphics/matrix.h ../../graphics/log.h
../src/scaled_frame.o: ../../graphics/vector.h ../../graphics/misc.h
../src/scaled_frame.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/scaled_frame.o: ../../graphics/matrix3x3.h
../src/scaled_frame.o: ../../graphics/EulerAngles.h
../src/scaled_frame.o: ../../graphics/QuatTypes.h ../../graphics/gl.h
../src/scaled_frame.o: ../../graphics/geom.h ../../graphics/unsigned.h
../src/scaled_frame.o: ../../graphics/color_buffer.h ../../graphics/gl_stat.h
../src/scaled_frame.o: ../../graphics/frame.h
../src/seed_fill.o: ../../graphics/seed_fill.h ../../graphics/geom.h
../src/seed_fill.o: ../../graphics/sys.h /usr/include/stdint.h
../src/seed_fill.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/seed_fill.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/seed_fill.o: ../../graphics/real.h ../../graphics/vec.h
../src/seed_fill.o: ../../graphics/ivec.h /usr/include/math.h
../src/seed_fill.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/seed_fill.o: ../../graphics/log.h ../../graphics/misc.h
../src/seed_fill.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/seed_fill.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/seed_fill.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/Shader.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/Shader.o: /usr/include/stdint.h /usr/include/stdio.h
../src/Shader.o: /usr/include/fcntl.h /usr/include/features.h
../src/Shader.o: /usr/include/stdc-predef.h
../src/shadow_map.o: ../../graphics/glInfo.h ../../graphics/shadow_map.h
../src/shadow_map.o: ../../graphics/camera.h ../../graphics/sys.h
../src/shadow_map.o: /usr/include/stdint.h /usr/include/stdio.h
../src/shadow_map.o: /usr/include/fcntl.h /usr/include/features.h
../src/shadow_map.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/shadow_map.o: ../../graphics/frame.h ../../graphics/vec.h
../src/shadow_map.o: ../../graphics/ivec.h /usr/include/math.h
../src/shadow_map.o: ../../graphics/epsilon.h ../../graphics/matrix.h
../src/shadow_map.o: ../../graphics/log.h ../../graphics/vector.h
../src/shadow_map.o: ../../graphics/misc.h ../../graphics/minmax.h
../src/shadow_map.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/shadow_map.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/shadow_map.o: ../../graphics/gl.h ../../graphics/geom.h
../src/shadow_map.o: ../../graphics/unsigned.h ../../graphics/color_buffer.h
../src/shadow_map.o: ../../graphics/gl_stat.h ../../graphics/virtual_model.h
../src/shadow_map.o: ../../graphics/CameraModeling.h
../src/shadow_map.o: ../../graphics/viewport.h
../src/shadow_map.o: ../../graphics/color_buffer64.h ../../graphics/teapot.h
../src/simple_b_rep.o: ../../graphics/simple_b_rep.h ../../graphics/vec.h
../src/simple_b_rep.o: ../../graphics/real.h /usr/include/stdio.h
../src/simple_b_rep.o: ../../graphics/ivec.h /usr/include/math.h
../src/simple_b_rep.o: ../../graphics/epsilon.h ../../graphics/Delaunay.h
../src/simple_curve.o: ../../graphics/simple_curve.h ../../graphics/real.h
../src/simple_curve.o: ../../graphics/vec.h /usr/include/stdio.h
../src/simple_curve.o: ../../graphics/ivec.h /usr/include/math.h
../src/simple_curve.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/simple_curve.o: ../../graphics/sys.h /usr/include/stdint.h
../src/simple_curve.o: /usr/include/fcntl.h /usr/include/features.h
../src/simple_curve.o: /usr/include/stdc-predef.h ../../graphics/log.h
../src/simple_curve.o: ../../graphics/misc.h
../src/SLIC.o: ../../graphics/SLIC.h
../src/slic_hierarchy.o: ../../graphics/slic_hierarchy.h
../src/slic_hierarchy.o: ../../graphics/geom.h ../../graphics/sys.h
../src/slic_hierarchy.o: /usr/include/stdint.h /usr/include/stdio.h
../src/slic_hierarchy.o: /usr/include/fcntl.h /usr/include/features.h
../src/slic_hierarchy.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/slic_hierarchy.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/slic_hierarchy.o: /usr/include/math.h ../../graphics/epsilon.h
../src/slic_hierarchy.o: ../../graphics/vector.h ../../graphics/log.h
../src/slic_hierarchy.o: ../../graphics/misc.h ../../graphics/matrix.h
../src/slic_hierarchy.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/slic_hierarchy.o: ../../graphics/matrix3x3.h
../src/slic_hierarchy.o: ../../graphics/EulerAngles.h
../src/slic_hierarchy.o: ../../graphics/QuatTypes.h ../../graphics/SLIC.h
../src/solve.o: ../../graphics/solve.h ../../graphics/sys.h
../src/solve.o: /usr/include/stdint.h /usr/include/stdio.h
../src/solve.o: /usr/include/fcntl.h /usr/include/features.h
../src/solve.o: /usr/include/stdc-predef.h ../../graphics/log.h
../src/solve.o: ../../graphics/real.h /usr/include/math.h
../src/solve.o: ../../graphics/vec.h ../../graphics/ivec.h
../src/solve.o: ../../graphics/epsilon.h ../../graphics/_limits.h
../src/solve.o: /usr/include/string.h
../src/square.o: ../../graphics/square.h ../../graphics/sys.h
../src/square.o: /usr/include/stdint.h /usr/include/stdio.h
../src/square.o: /usr/include/fcntl.h /usr/include/features.h
../src/square.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/StreamTexture.o: ../../graphics/StreamTexture.h
../src/StreamTexture.o: ../../graphics/gl_extension.h ../../graphics/sys.h
../src/StreamTexture.o: /usr/include/stdint.h /usr/include/stdio.h
../src/StreamTexture.o: /usr/include/fcntl.h /usr/include/features.h
../src/StreamTexture.o: /usr/include/stdc-predef.h ../../graphics/unsigned.h
../src/StreamTexture.o: ../../graphics/real.h
../src/StreamTextureRGB.o: ../../graphics/StreamTextureRGB.h
../src/StreamTextureRGB.o: ../../graphics/gl_extension.h ../../graphics/sys.h
../src/StreamTextureRGB.o: /usr/include/stdint.h /usr/include/stdio.h
../src/StreamTextureRGB.o: /usr/include/fcntl.h /usr/include/features.h
../src/StreamTextureRGB.o: /usr/include/stdc-predef.h
../src/StreamTextureRGB.o: ../../graphics/unsigned.h ../../graphics/real.h
../src/string_manip.o: ../../graphics/string_manip.h /usr/include/string.h
../src/string_manip.o: ../../graphics/sys.h /usr/include/stdint.h
../src/string_manip.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/string_manip.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/string_manip.o: ../../graphics/minmax.h ../../graphics/real.h
../src/sys.o: ../../graphics/sys.h /usr/include/stdint.h /usr/include/stdio.h
../src/sys.o: /usr/include/fcntl.h /usr/include/features.h
../src/sys.o: /usr/include/stdc-predef.h ../../graphics/string_manip.h
../src/TextTexture.o: ../../graphics/TextTexture.h ../../graphics/geom.h
../src/TextTexture.o: ../../graphics/sys.h /usr/include/stdint.h
../src/TextTexture.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/TextTexture.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/TextTexture.o: ../../graphics/real.h ../../graphics/vec.h
../src/TextTexture.o: ../../graphics/ivec.h /usr/include/math.h
../src/TextTexture.o: ../../graphics/epsilon.h ../../graphics/vector.h
../src/TextTexture.o: ../../graphics/log.h ../../graphics/misc.h
../src/TextTexture.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/TextTexture.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/TextTexture.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/TextTexture.o: ../../graphics/glInfo.h ../../graphics/gl_stat.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/QImage
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qimage.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtguiglobal.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qglobal.h
../src/TextTexture.o: /usr/include/assert.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qconfig.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qtcore-config.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qsystemdetection.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qprocessordetection.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qcompilerdetection.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtgui-config.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qcolor.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qrgb.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qnamespace.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringlist.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qlist.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qalgorithms.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qiterator.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qrefcount.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qatomic.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qbasicatomic.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qarraydata.h
../src/TextTexture.o: /usr/include/string.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qhashfunctions.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstring.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qchar.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qbytearray.h
../src/TextTexture.o: /usr/include/stdlib.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringliteral.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringalgorithms.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringview.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qpair.h
../src/TextTexture.o: /usr/include/limits.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qbytearraylist.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qregexp.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qstringmatcher.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qrgba64.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpaintdevice.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qwindowdefs.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobjectdefs.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobjectdefs_impl.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qrect.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qmargins.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qsize.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qpoint.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpixelformat.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtransform.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qmatrix.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpolygon.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qvector.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qregion.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qdatastream.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qscopedpointer.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qiodevice.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobject.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qmetatype.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qvarlengtharray.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qcontainerfwd.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qobject_impl.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qline.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpainterpath.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/QBrush
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qbrush.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qimage.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpixmap.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qsharedpointer.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qshareddata.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qhash.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qsharedpointer_impl.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/QPen
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpen.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qbrush.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/QPainter
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpainter.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtextoption.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qpen.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qfontinfo.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qfont.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qfontmetrics.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/QTextLayout
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtextlayout.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qevent.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qkeysequence.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qcoreevent.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qvariant.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qmap.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qset.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qurl.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qurlquery.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qfile.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtCore/qfiledevice.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qvector2d.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtouchdevice.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtextformat.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qglyphrun.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qrawfont.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qfontdatabase.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtextcursor.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/QTextBlock
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtextobject.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtextlayout.h
../src/TextTexture.o: /usr/include/x86_64-linux-gnu/qt5/QtGui/qtextdocument.h
../src/texture_buffer.o: ../../graphics/texture_buffer.h ../../graphics/sys.h
../src/texture_buffer.o: /usr/include/stdint.h /usr/include/stdio.h
../src/texture_buffer.o: /usr/include/fcntl.h /usr/include/features.h
../src/texture_buffer.o: /usr/include/stdc-predef.h ../../graphics/gl.h
../src/texture_buffer.o: ../../graphics/real.h ../../graphics/vec.h
../src/texture_buffer.o: ../../graphics/ivec.h /usr/include/math.h
../src/texture_buffer.o: ../../graphics/epsilon.h ../../graphics/misc.h
../src/texture_buffer.o: ../../graphics/geom.h ../../graphics/vector.h
../src/texture_buffer.o: ../../graphics/log.h ../../graphics/matrix.h
../src/texture_buffer.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/texture_buffer.o: ../../graphics/matrix3x3.h
../src/texture_buffer.o: ../../graphics/EulerAngles.h
../src/texture_buffer.o: ../../graphics/QuatTypes.h ../../graphics/unsigned.h
../src/texture_buffer.o: ../../graphics/color_buffer.h
../src/texture_buffer.o: ../../graphics/gl_stat.h
../src/texture_buffer.o: ../../graphics/gl_extension.h
../src/texture_buffer_ms.o: ../../graphics/texture_buffer_ms.h
../src/texture_buffer_ms.o: ../../graphics/sys.h /usr/include/stdint.h
../src/texture_buffer_ms.o: /usr/include/stdio.h /usr/include/fcntl.h
../src/texture_buffer_ms.o: /usr/include/features.h
../src/texture_buffer_ms.o: /usr/include/stdc-predef.h ../../graphics/gl.h
../src/texture_buffer_ms.o: ../../graphics/real.h ../../graphics/vec.h
../src/texture_buffer_ms.o: ../../graphics/ivec.h /usr/include/math.h
../src/texture_buffer_ms.o: ../../graphics/epsilon.h ../../graphics/misc.h
../src/texture_buffer_ms.o: ../../graphics/geom.h ../../graphics/vector.h
../src/texture_buffer_ms.o: ../../graphics/log.h ../../graphics/matrix.h
../src/texture_buffer_ms.o: ../../graphics/minmax.h ../../graphics/quater.h
../src/texture_buffer_ms.o: ../../graphics/matrix3x3.h
../src/texture_buffer_ms.o: ../../graphics/EulerAngles.h
../src/texture_buffer_ms.o: ../../graphics/QuatTypes.h
../src/texture_buffer_ms.o: ../../graphics/unsigned.h
../src/texture_buffer_ms.o: ../../graphics/color_buffer.h
../src/texture_buffer_ms.o: ../../graphics/gl_stat.h
../src/texture_buffer_ms.o: ../../graphics/gl_extension.h
../src/texture_buffer_ms.o: ../../graphics/texture_buffer.h
../src/Timer.o: ../../graphics/Timer.h /usr/include/stdlib.h
../src/Triangle.o: ../../graphics/Triangle.h ../../graphics/vec.h
../src/Triangle.o: ../../graphics/real.h /usr/include/stdio.h
../src/Triangle.o: ../../graphics/ivec.h /usr/include/math.h
../src/Triangle.o: ../../graphics/epsilon.h
../src/unsigned.o: ../../graphics/unsigned.h
../src/vec.o: ../../graphics/vec.h ../../graphics/real.h /usr/include/stdio.h
../src/vec.o: ../../graphics/ivec.h /usr/include/math.h
../src/vec.o: ../../graphics/epsilon.h ../../graphics/solve.h
../src/vec.o: ../../graphics/sys.h /usr/include/stdint.h /usr/include/fcntl.h
../src/vec.o: /usr/include/features.h /usr/include/stdc-predef.h
../src/vec.o: ../../graphics/log.h
../src/vector.o: ../../graphics/vector.h ../../graphics/sys.h
../src/vector.o: /usr/include/stdint.h /usr/include/stdio.h
../src/vector.o: /usr/include/fcntl.h /usr/include/features.h
../src/vector.o: /usr/include/stdc-predef.h ../../graphics/log.h
../src/vector.o: ../../graphics/misc.h ../../graphics/real.h
../src/vector.o: /usr/include/math.h
../src/fvec.o: ../../graphics/fvec.h ../../graphics/real.h
../src/fvec.o: /usr/include/stdio.h ../../graphics/ivec.h /usr/include/math.h
../src/fvec.o: ../../graphics/epsilon.h ../../graphics/solve.h
../src/fvec.o: ../../graphics/sys.h /usr/include/stdint.h
../src/fvec.o: /usr/include/fcntl.h /usr/include/features.h
../src/fvec.o: /usr/include/stdc-predef.h ../../graphics/log.h
../src/virtual_model.o: ../../graphics/virtual_model.h ../../graphics/vec.h
../src/virtual_model.o: ../../graphics/real.h /usr/include/stdio.h
../src/virtual_model.o: ../../graphics/ivec.h /usr/include/math.h
../src/virtual_model.o: ../../graphics/epsilon.h ../../graphics/geom.h
../src/virtual_model.o: ../../graphics/sys.h /usr/include/stdint.h
../src/virtual_model.o: /usr/include/fcntl.h /usr/include/features.h
../src/virtual_model.o: /usr/include/stdc-predef.h ../../graphics/vector.h
../src/virtual_model.o: ../../graphics/log.h ../../graphics/misc.h
../src/virtual_model.o: ../../graphics/matrix.h ../../graphics/minmax.h
../src/virtual_model.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/virtual_model.o: ../../graphics/EulerAngles.h
../src/virtual_model.o: ../../graphics/QuatTypes.h
../src/xform.o: ../../graphics/real.h ../../graphics/xform.h
../src/xform.o: ../../graphics/vec.h /usr/include/stdio.h
../src/xform.o: ../../graphics/ivec.h /usr/include/math.h
../src/xform.o: ../../graphics/epsilon.h ../../graphics/frame.h
../src/xform.o: ../../graphics/sys.h /usr/include/stdint.h
../src/xform.o: /usr/include/fcntl.h /usr/include/features.h
../src/xform.o: /usr/include/stdc-predef.h ../../graphics/matrix.h
../src/xform.o: ../../graphics/log.h ../../graphics/vector.h
../src/xform.o: ../../graphics/misc.h ../../graphics/minmax.h
../src/xform.o: ../../graphics/quater.h ../../graphics/matrix3x3.h
../src/xform.o: ../../graphics/EulerAngles.h ../../graphics/QuatTypes.h
../src/xform.o: ../../graphics/gl.h ../../graphics/geom.h
../src/xform.o: ../../graphics/unsigned.h ../../graphics/color_buffer.h
../src/xform.o: ../../graphics/gl_stat.h
../src/YUVtoRGB_Shader.o: ../../graphics/YUVtoRGB_Shader.h
../src/YUVtoRGB_Shader.o: ../../graphics/Shader.h ../../graphics/sys.h
../src/YUVtoRGB_Shader.o: /usr/include/stdint.h /usr/include/stdio.h
../src/YUVtoRGB_Shader.o: /usr/include/fcntl.h /usr/include/features.h
../src/YUVtoRGB_Shader.o: /usr/include/stdc-predef.h
../src/_limits.o: ../../graphics/_limits.h ../../graphics/sys.h
../src/_limits.o: /usr/include/stdint.h /usr/include/stdio.h
../src/_limits.o: /usr/include/fcntl.h /usr/include/features.h
../src/_limits.o: /usr/include/stdc-predef.h ../../graphics/real.h
../src/_limits.o: /usr/include/limits.h
