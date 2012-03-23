#ifndef SM_OPENCV_SERIALIZATION_HPP
#define SM_OPENCV_SERIALIZATION_HPP


#include <opencv2/core/core.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/split_free.hpp>


namespace boost {
  namespace serialization {

template<class Archive>
void serialize(Archive & ar, cv::Point2f & p, const unsigned int version)
{
  ar & BOOST_SERIALIZATION_NVP(p.x);
  ar & BOOST_SERIALIZATION_NVP(p.y);
}

template<class Archive>
void serialize(Archive & ar, cv::KeyPoint & k, const unsigned int version)
{
  ar & BOOST_SERIALIZATION_NVP(k.pt);
  ar & BOOST_SERIALIZATION_NVP(k.size);
  ar & BOOST_SERIALIZATION_NVP(k.angle);
  ar & BOOST_SERIALIZATION_NVP(k.response);
  ar & BOOST_SERIALIZATION_NVP(k.octave);
  ar & BOOST_SERIALIZATION_NVP(k.class_id);
}


  } // namespace serialization
} // namespace boost

 /*
  * From the WillowGarage "ReIn" project.
  * serialization_support.h
  *
  * Software License Agreement (BSD License)
  *
  *  Copyright (c) 2009, Willow Garage, Inc.
  *  All rights reserved.
  *
  *  Redistribution and use in source and binary forms, with or without
  *  modification, are permitted provided that the following conditions
  *  are met:
  *
  *   * Redistributions of source code must retain the above copyright
  *     notice, this list of conditions and the following disclaimer.
  *   * Redistributions in binary form must reproduce the above
  *     copyright notice, this list of conditions and the following
  *     disclaimer in the documentation and/or other materials provided
  *     with the distribution.
  *   * Neither the name of Willow Garage, Inc. nor the names of its
  *     contributors may be used to endorse or promote products derived
  *     from this software without specific prior written permission.
  *
  *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  *  POSSIBILITY OF SUCH DAMAGE.
  *
  * $Id$
  *
  */


// ------------- cv::Mat
namespace boost 
{ 
  namespace serialization 
  {
 
    template<class Archive>
    void save(Archive & ar, const cv::Mat& mat, const unsigned int version)
    {
      using namespace boost::serialization;
      cv::Mat mat_;
      mat_ = mat;
      if (!mat.isContinuous()) {
	mat_ = mat.clone();
	//          throw rein::Exception("Only serialising continuous cv::Mat objects");
      }
      int type = mat_.type();
      ar & make_nvp("rows",mat_.rows);
      ar & make_nvp("cols",mat_.cols);
      ar & make_nvp("type",type);
      ar & make_nvp("data",boost::serialization::make_binary_object(mat_.data, mat_.step*mat_.rows));
    }
 
    template<class Archive>
    void load(Archive & ar, cv::Mat& mat, const unsigned int version)
    {
      int rows, cols, type;
      ar & rows;
      ar & cols;
      ar & type;
      mat.create(rows, cols, type);
      ar & boost::serialization::make_binary_object(mat.data, mat.step*mat.rows);
    }
 
  }} // namespace boost::serialization.
BOOST_SERIALIZATION_SPLIT_FREE(cv::Mat);



#endif /* SM_OPENCV_SERIALIZATION_HPP */