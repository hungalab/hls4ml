//
//    rfnoc-hls-neuralnet: Vivado HLS code for neural-net building blocks
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////
//
// Keras trained accuracy 98.89%
// 16-bit 98.87%

#include <iostream>

#include "parameters.h"
#include "lenet5.h"

#include "nnet_layer.h"
#include "nnet_conv.h"
#include "nnet_conv2d.h"
#include "nnet_batchnorm.h"
#include "nnet_activation.h"
#include "nnet_pooling.h"

//hls-fpga-machine-learning insert weights
#include "weights/w1.h"
#include "weights/b1.h"
#include "weights/w3.h"
#include "weights/b3.h"
#include "weights/w5.h"
#include "weights/b5.h"
#include "weights/w6.h"
#include "weights/b6.h"
#include "weights/w7.h"
#include "weights/b7.h"

void lenet5(
		  input_t data[IN_HEIGHT_1][IN_WIDTH_1][N_CHAN_1],
		  result_t res[N_OUTPUTS],
		  unsigned short &const_size_in,
		  unsigned short &const_size_out)
{

    //hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=data,res 
    #pragma HLS DATAFLOW 


    const_size_in   = IN_HEIGHT_1*IN_WIDTH_1*N_CHAN_1;
    const_size_out  = N_OUTPUTS;

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    //hls-fpga-machine-learning insert layers

    layer1_t layer1_out[OUT_HEIGHT_1*OUT_WIDTH_1*N_FILT_1];

    layer1_t conv2d_layer1_out[OUT_HEIGHT_1][OUT_WIDTH_1][N_FILT_1];

    nnet::conv_2d<input_t, layer1_t, config1>(data, conv2d_layer1_out, w1, b1);
    layer1_t logits1[OUT_HEIGHT_1*OUT_WIDTH_1*N_FILT_1];

    nnet::flatten<layer1_t, OUT_HEIGHT_1, OUT_WIDTH_1, N_FILT_1>(conv2d_layer1_out, logits1);
    nnet::relu<layer1_t, layer1_t, relu_config1>(logits1, layer1_out);

    layer1_t layer2_out[OUT_HEIGHT_2*OUT_WIDTH_2*N_FILT_2];

    layer1_t pool2d_layer2_in[IN_HEIGHT_2][IN_WIDTH_2][N_FILT_2];

    nnet::unflatten<layer1_t, IN_HEIGHT_2, IN_WIDTH_2, N_FILT_2>(layer1_out, pool2d_layer2_in);
    layer1_t pool2d_layer2_out[OUT_HEIGHT_2][OUT_WIDTH_2][N_FILT_2];

    nnet::pooling2d<layer1_t, config2>(pool2d_layer2_in, pool2d_layer2_out);

    layer3_t layer3_out[OUT_HEIGHT_3*OUT_WIDTH_3*N_FILT_3];

    layer3_t conv2d_layer3_out[OUT_HEIGHT_3][OUT_WIDTH_3][N_FILT_3];

    nnet::conv_2d<layer2_t, layer3_t, config3>(pool2d_layer2_out, conv2d_layer3_out, w3, b3);
    layer3_t logits3[OUT_HEIGHT_3*OUT_WIDTH_3*N_FILT_3];

    nnet::flatten<layer3_t, OUT_HEIGHT_3, OUT_WIDTH_3, N_FILT_3>(conv2d_layer3_out, logits3);
    nnet::relu<layer3_t, layer3_t, relu_config3>(logits3, layer3_out);

    layer3_t layer4_out[OUT_HEIGHT_4*OUT_WIDTH_4*N_FILT_4];

    layer3_t pool2d_layer4_in[IN_HEIGHT_4][IN_WIDTH_4][N_FILT_4];

    nnet::unflatten<layer3_t, IN_HEIGHT_4, IN_WIDTH_4, N_FILT_4>(layer3_out, pool2d_layer4_in);
    layer3_t pool2d_layer4_out[OUT_HEIGHT_4][OUT_WIDTH_4][N_FILT_4];

    nnet::pooling2d<layer3_t, config4>(pool2d_layer4_in, pool2d_layer4_out);
    nnet::flatten<layer3_t, OUT_HEIGHT_4, OUT_WIDTH_4, N_FILT_4>(pool2d_layer4_out, layer4_out);

    layer5_t layer5_out[N_LAYER_5];

    layer5_t logits5[N_LAYER_5];

    nnet::compute_layer<layer4_t, layer5_t, config5>(layer4_out, logits5, w5, b5);
    nnet::relu<layer5_t, layer5_t, relu_config5>(logits5, layer5_out);

    layer6_t layer6_out[N_LAYER_6];

    layer6_t logits6[N_LAYER_6];

    nnet::compute_layer<layer5_t, layer6_t, config6>(layer5_out, logits6, w6, b6);
    nnet::relu<layer6_t, layer6_t, relu_config6>(logits6, layer6_out);

    result_t logits7[N_OUTPUTS];

    nnet::compute_layer<layer6_t, result_t, config7>(layer6_out, res, w7, b7);

    // softmax causes accuracy to drop
//    nnet::softmax<result_t, result_t, softmax_config7>(logits7, res);

}
