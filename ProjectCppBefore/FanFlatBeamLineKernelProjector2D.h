#ifndef _INC_ASTRA_FANFLATBEAMLINEKERNELPROJECTOR
#define _INC_ASTRA_FANFLATBEAMLINEKERNELPROJECTOR

#include "FanFlatProjectionGeometry2D.h"
#include "FanFlatVecProjectionGeometry2D.h"
#include "Float32Data2D.h"
#include "Projector2D.h"


/** This class implements a two-dimensional projector based on a line based kernel
	* with a fan flat projection geometry.
	*/
class CFanFlatBeamLineKernelProjector2D : public CProjector2D {

protected:

	/** Initial clearing. Only to be used by constructors.
		*/
	virtual void _clear();

	/** Check the values of this object.  If everything is ok, the object can be set to the initialized state.
		* The following statements are then guaranteed to hold:
		* - no NULL pointers
		* - all sub-objects are initialized properly
		* - blobvalues are ok
		*/
	virtual bool _check();

public:

	// type of the projector, needed to register with CProjectorFactory
	static std::string type;

	/** Default constructor.
		*/
	CFanFlatBeamLineKernelProjector2D();

	/** Constructor.
		*
		* @param _pProjectionGeometry		Information class about the geometry of the projection.  Will be HARDCOPIED.
		* @param _pReconstructionGeometry	Information class about the geometry of the reconstruction volume. Will be HARDCOPIED.
		*/
	CFanFlatBeamLineKernelProjector2D(CFanFlatProjectionGeometry2D* _pProjectionGeometry,
		CVolumeGeometry2D* _pReconstructionGeometry);

	/** Destructor, is virtual to show that we are aware subclass destructor are called.
		*/
	~CFanFlatBeamLineKernelProjector2D();

	/** Initialize the projector.
		*
		* @param _pProjectionGeometry		Information class about the geometry of the projection. Will be HARDCOPIED.
		* @param _pReconstructionGeometry	Information class about the geometry of the reconstruction volume. Will be HARDCOPIED.
		* @return initialization successful?
		*/
	virtual bool initialize(CFanFlatProjectionGeometry2D* _pProjectionGeometry,
		CVolumeGeometry2D* _pReconstructionGeometry);

	/** Clear this class.
		*/
	virtual void clear();

	/** Returns the number of weights required for storage of all weights of one projection.
		*
		* @param _iProjectionIndex Index of the projection (zero-based).
		* @return Size of buffer (given in SPixelWeight elements) needed to store weighted pixels.
		*/
	virtual int getProjectionWeightsCount(int _iProjectionIndex);

	/** Compute the pixel weights for a single ray, from the source to a detector pixel.
		*
		* @param _iProjectionIndex	Index of the projection
		* @param _iDetectorIndex	Index of the detector pixel
		* @param _pWeightedPixels	Pointer to a pre-allocated array, consisting of _iMaxPixelCount elements
		*							of type SPixelWeight. On return, this array contains a list of the index
		*							and weight for all pixels on the ray.
		* @param _iMaxPixelCount	Maximum number of pixels (and corresponding weights) that can be stored in _pWeightedPixels.
		*							This number MUST be greater than the total number of pixels on the ray.
		* @param _iStoredPixelCount On return, this variable contains the total number of pixels on the
		*                           ray (that have been stored in the list _pWeightedPixels).
		*/
	virtual void computeSingleRayWeights(int _iProjectionIndex,
		int _iDetectorIndex,
		SPixelWeight* _pWeightedPixels,
		int _iMaxPixelCount,
		int& _iStoredPixelCount);

	/** Policy-based projection of all rays.  This function will calculate each non-zero projection
		* weight and use this value for a task provided by the policy object.
		*
		* @param _policy Policy object.  Should contain prior, addWeight and posterior function.
		*/
	template <typename Policy>
	void project(Policy& _policy);

	/** Policy-based projection of all rays of a single projection.  This function will calculate
		* each non-zero projection weight and use this value for a task provided by the policy object.
		*
		* @param _iProjection Wwhich projection should be projected?
		* @param _policy Policy object.  Should contain prior, addWeight and posterior function.
		*/
	template <typename Policy>
	void projectSingleProjection(int _iProjection, Policy& _policy);

	/** Policy-based projection of a single ray.  This function will calculate each non-zero
		* projection  weight and use this value for a task provided by the policy object.
		*
		* @param _iProjection Which projection should be projected?
		* @param _iDetector Which detector should be projected?
		* @param _policy Policy object.  Should contain prior, addWeight and posterior function.
		*/
	template <typename Policy>
	void projectSingleRay(int _iProjection, int _iDetector, Policy& _policy);

	/** Return the type of this projector.
		*
		* @return identification type of this projector
		*/
	virtual std::string getType();

	float angleBetweenVectors(float _fAX, float _fAY, float _fBX, float _fBY);

protected:
	/** Internal policy-based projection of a range of angles and range.
		* (_i*From is inclusive, _i*To exclusive) */
	template <typename Policy>
	void projectBlock_internal(int _iProjFrom, int _iProjTo,
		int _iDetFrom, int _iDetTo, Policy& _policy);

};

//----------------------------------------------------------------------------------------

inline std::string CFanFlatBeamLineKernelProjector2D::getType()
{
	return type;
}



#endif 

