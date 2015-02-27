/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkMeanSquaresPointSetToPointSetIntensityMetricv4_h
#define itkMeanSquaresPointSetToPointSetIntensityMetricv4_h

#include "itkPointSetToPointSetMetricv4.h"

namespace itk
{
/** \class MeanSquaresPointSetToPointSetIntensityMetricv4
 * \brief Computes a mean-squares intensity metric between two point sets.
 *
 *  We only have to handle the individual point case as the parent
 *  class handles the aggregation.
 *
 *  The PointSet::PixelType contains both the intensity and gradient
 *  information at each point and the surrounding neighborhood.  The ordering
 *  is based on the itk::Neighborhood data structure:
 *
 *  http://www.itk.org/Doxygen/html/classitk_1_1Neighborhood.html
 *
 *  pixelData = [intensity_0, gradientX_0, gradientY_0, gradientZ_0,       // GetOffset( 0 )
 *               intensity_1, gradientX_1, gradientY_1, gradientZ_1,       // GetOffset( 1 )
 *               ...        , ...        , ...        , ...        ,         ...
 *               intensity_N, gradientX_N, gradientY_N, gradientZ_N]       // GetOffset( N )
 *
 *
 * \ingroup ITKMetricsv4
 */
template<typename TFixedPointSet, typename TMovingPointSet = TFixedPointSet,
  class TInternalComputationValueType = double>
class MeanSquaresPointSetToPointSetIntensityMetricv4:
  public PointSetToPointSetMetricv4<TFixedPointSet, TMovingPointSet, TInternalComputationValueType>
{
public:

  /** Standard class typedefs. */
  typedef MeanSquaresPointSetToPointSetIntensityMetricv4               Self;
  typedef PointSetToPointSetMetricv4<TFixedPointSet, TMovingPointSet,
    TInternalComputationValueType>                                     Superclass;
  typedef SmartPointer<Self>                                           Pointer;
  typedef SmartPointer<const Self>                                     ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( MeanSquaresPointSetToPointSetIntensityMetricv4, PointSetToPointSetMetricv4 );

  /**  Type of the fixed point set. */
  typedef TFixedPointSet                               FixedPointSetType;
  typedef typename TFixedPointSet::PointType           FixedPointType;
  typedef typename TFixedPointSet::PixelType           FixedPixelType;
  typedef typename TFixedPointSet::PointsContainer     FixedPointsContainer;
  typedef typename TFixedPointSet::PointDataContainer  FixedPointDataContainer;

  itkStaticConstMacro( FixedPointDimension, DimensionType, Superclass::FixedDimension );

  /**  Type of the moving point set. */
  typedef TMovingPointSet                              MovingPointSetType;
  typedef typename TMovingPointSet::PointType          MovingPointType;
  typedef typename TMovingPointSet::PixelType          MovingPixelType;
  typedef typename TMovingPointSet::PointsContainer    MovingPointsContainer;

  itkStaticConstMacro( MovingPointDimension, DimensionType, Superclass::MovingDimension );

  /** Transform types from Superclass*/
  typedef typename Superclass::FixedTransformType            FixedTransformType;

  /** Dimension type */
  typedef typename Superclass::DimensionType                  DimensionType;

  itkStaticConstMacro( PointDimension, DimensionType, Superclass::PointDimension );

  /** Types transferred from the base class */
  typedef typename Superclass::MeasureType             MeasureType;
  typedef typename Superclass::DerivativeType          DerivativeType;
  typedef typename Superclass::LocalDerivativeType     LocalDerivativeType;
  typedef typename Superclass::PointType               PointType;
  typedef typename Superclass::PixelType               PixelType;
  typedef typename Superclass::PointIdentifier         PointIdentifier;

  /**
   * Calculates the local metric value for a single point.
   */
  virtual MeasureType GetLocalNeighborhoodValue( const PointType &, const PixelType & pixel = 0 ) const ITK_OVERRIDE;

  /** Helper method allows for code reuse while skipping the metric value
   * calculation when appropriate */
  void CalculateValueAndDerivative( MeasureType & value, DerivativeType & derivative, bool calculateValue ) const;

  /**
   * Calculates the local value and derivative for a single point.
   */
  virtual void GetLocalNeighborhoodValueAndDerivative( const PointType &,
    MeasureType &, LocalDerivativeType &, const PixelType & pixel = 0 ) const ITK_OVERRIDE;

  /** Clone method will clone the existing instance of this type,
   *  including its internal member variables. */
  virtual typename LightObject::Pointer InternalClone() const ITK_OVERRIDE;

protected:
  MeanSquaresPointSetToPointSetIntensityMetricv4();
  virtual ~MeanSquaresPointSetToPointSetIntensityMetricv4();

  /** PrintSelf function */
  void PrintSelf( std::ostream & os, Indent indent ) const ITK_OVERRIDE;

private:
  MeanSquaresPointSetToPointSetIntensityMetricv4(const Self &); //purposely not implemented
  void operator=(const Self &);               //purposely not implemented
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMeanSquaresPointSetToPointSetIntensityMetricv4.hxx"
#endif

#endif
