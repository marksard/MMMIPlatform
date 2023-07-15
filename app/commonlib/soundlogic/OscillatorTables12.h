/*!
 * Oscillator Tables
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */ 

#pragma once

#define MAX_OCT 10
#define MAX_SEMI 12
#define MAX_VOCT 4096
// ------------------------- C-2-C7(Hz) -------------------------
const static float octaves[MAX_OCT] PROGMEM = {
8.175799,
16.351598,
32.703196,
65.406392,
130.812784,
261.625568,
523.251136,
1046.502272,
2093.004544,
4186.009088,
};

// ------------------------- semitones -------------------------
const static float semitones[MAX_SEMI] PROGMEM = {
1.0,
1.059463,
1.122462,
1.189207,
1.259921,
1.33484,
1.414214,
1.498307,
1.587401,
1.681793,
1.781797,
1.887749,
};

// ------------------------- volt_table_pow2 -------------------------
const static float volt_table_pow2[MAX_VOCT] PROGMEM = {
1.0,
1.0008,
1.0017,
1.0025,
1.0034,
1.0042,
1.0051,
1.0059,
1.0068,
1.0076,
1.0085,
1.0094,
1.0102,
1.0111,
1.0119,
1.0128,
1.0136,
1.0145,
1.0153,
1.0162,
1.0171,
1.0179,
1.0188,
1.0197,
1.0205,
1.0214,
1.0222,
1.0231,
1.024,
1.0248,
1.0257,
1.0266,
1.0274,
1.0283,
1.0292,
1.0301,
1.0309,
1.0318,
1.0327,
1.0335,
1.0344,
1.0353,
1.0362,
1.0371,
1.0379,
1.0388,
1.0397,
1.0406,
1.0415,
1.0423,
1.0432,
1.0441,
1.045,
1.0459,
1.0468,
1.0476,
1.0485,
1.0494,
1.0503,
1.0512,
1.0521,
1.053,
1.0539,
1.0548,
1.0556,
1.0565,
1.0574,
1.0583,
1.0592,
1.0601,
1.061,
1.0619,
1.0628,
1.0637,
1.0646,
1.0655,
1.0664,
1.0673,
1.0682,
1.0691,
1.07,
1.0709,
1.0718,
1.0728,
1.0737,
1.0746,
1.0755,
1.0764,
1.0773,
1.0782,
1.0791,
1.08,
1.081,
1.0819,
1.0828,
1.0837,
1.0846,
1.0855,
1.0865,
1.0874,
1.0883,
1.0892,
1.0901,
1.0911,
1.092,
1.0929,
1.0938,
1.0948,
1.0957,
1.0966,
1.0975,
1.0985,
1.0994,
1.1003,
1.1013,
1.1022,
1.1031,
1.1041,
1.105,
1.1059,
1.1069,
1.1078,
1.1087,
1.1097,
1.1106,
1.1116,
1.1125,
1.1134,
1.1144,
1.1153,
1.1163,
1.1172,
1.1182,
1.1191,
1.1201,
1.121,
1.122,
1.1229,
1.1239,
1.1248,
1.1258,
1.1267,
1.1277,
1.1286,
1.1296,
1.1305,
1.1315,
1.1324,
1.1334,
1.1344,
1.1353,
1.1363,
1.1372,
1.1382,
1.1392,
1.1401,
1.1411,
1.1421,
1.143,
1.144,
1.145,
1.1459,
1.1469,
1.1479,
1.1489,
1.1498,
1.1508,
1.1518,
1.1527,
1.1537,
1.1547,
1.1557,
1.1567,
1.1576,
1.1586,
1.1596,
1.1606,
1.1616,
1.1625,
1.1635,
1.1645,
1.1655,
1.1665,
1.1675,
1.1685,
1.1694,
1.1704,
1.1714,
1.1724,
1.1734,
1.1744,
1.1754,
1.1764,
1.1774,
1.1784,
1.1794,
1.1804,
1.1814,
1.1824,
1.1834,
1.1844,
1.1854,
1.1864,
1.1874,
1.1884,
1.1894,
1.1904,
1.1914,
1.1924,
1.1934,
1.1945,
1.1955,
1.1965,
1.1975,
1.1985,
1.1995,
1.2005,
1.2015,
1.2026,
1.2036,
1.2046,
1.2056,
1.2066,
1.2077,
1.2087,
1.2097,
1.2107,
1.2118,
1.2128,
1.2138,
1.2148,
1.2159,
1.2169,
1.2179,
1.219,
1.22,
1.221,
1.2221,
1.2231,
1.2241,
1.2252,
1.2262,
1.2272,
1.2283,
1.2293,
1.2304,
1.2314,
1.2324,
1.2335,
1.2345,
1.2356,
1.2366,
1.2377,
1.2387,
1.2398,
1.2408,
1.2419,
1.2429,
1.244,
1.245,
1.2461,
1.2471,
1.2482,
1.2492,
1.2503,
1.2514,
1.2524,
1.2535,
1.2545,
1.2556,
1.2567,
1.2577,
1.2588,
1.2598,
1.2609,
1.262,
1.2631,
1.2641,
1.2652,
1.2663,
1.2673,
1.2684,
1.2695,
1.2706,
1.2716,
1.2727,
1.2738,
1.2749,
1.2759,
1.277,
1.2781,
1.2792,
1.2803,
1.2814,
1.2824,
1.2835,
1.2846,
1.2857,
1.2868,
1.2879,
1.289,
1.2901,
1.2911,
1.2922,
1.2933,
1.2944,
1.2955,
1.2966,
1.2977,
1.2988,
1.2999,
1.301,
1.3021,
1.3032,
1.3043,
1.3054,
1.3065,
1.3076,
1.3087,
1.3099,
1.311,
1.3121,
1.3132,
1.3143,
1.3154,
1.3165,
1.3176,
1.3187,
1.3199,
1.321,
1.3221,
1.3232,
1.3243,
1.3255,
1.3266,
1.3277,
1.3288,
1.33,
1.3311,
1.3322,
1.3333,
1.3345,
1.3356,
1.3367,
1.3379,
1.339,
1.3401,
1.3413,
1.3424,
1.3435,
1.3447,
1.3458,
1.3469,
1.3481,
1.3492,
1.3504,
1.3515,
1.3527,
1.3538,
1.3549,
1.3561,
1.3572,
1.3584,
1.3595,
1.3607,
1.3618,
1.363,
1.3641,
1.3653,
1.3665,
1.3676,
1.3688,
1.3699,
1.3711,
1.3722,
1.3734,
1.3746,
1.3757,
1.3769,
1.3781,
1.3792,
1.3804,
1.3816,
1.3827,
1.3839,
1.3851,
1.3863,
1.3874,
1.3886,
1.3898,
1.391,
1.3921,
1.3933,
1.3945,
1.3957,
1.3969,
1.398,
1.3992,
1.4004,
1.4016,
1.4028,
1.404,
1.4051,
1.4063,
1.4075,
1.4087,
1.4099,
1.4111,
1.4123,
1.4135,
1.4147,
1.4159,
1.4171,
1.4183,
1.4195,
1.4207,
1.4219,
1.4231,
1.4243,
1.4255,
1.4267,
1.4279,
1.4291,
1.4303,
1.4316,
1.4328,
1.434,
1.4352,
1.4364,
1.4376,
1.4388,
1.4401,
1.4413,
1.4425,
1.4437,
1.4449,
1.4462,
1.4474,
1.4486,
1.4498,
1.4511,
1.4523,
1.4535,
1.4548,
1.456,
1.4572,
1.4584,
1.4597,
1.4609,
1.4622,
1.4634,
1.4646,
1.4659,
1.4671,
1.4684,
1.4696,
1.4708,
1.4721,
1.4733,
1.4746,
1.4758,
1.4771,
1.4783,
1.4796,
1.4808,
1.4821,
1.4833,
1.4846,
1.4859,
1.4871,
1.4884,
1.4896,
1.4909,
1.4922,
1.4934,
1.4947,
1.4959,
1.4972,
1.4985,
1.4997,
1.501,
1.5023,
1.5036,
1.5048,
1.5061,
1.5074,
1.5087,
1.5099,
1.5112,
1.5125,
1.5138,
1.515,
1.5163,
1.5176,
1.5189,
1.5202,
1.5215,
1.5228,
1.524,
1.5253,
1.5266,
1.5279,
1.5292,
1.5305,
1.5318,
1.5331,
1.5344,
1.5357,
1.537,
1.5383,
1.5396,
1.5409,
1.5422,
1.5435,
1.5448,
1.5461,
1.5474,
1.5487,
1.5501,
1.5514,
1.5527,
1.554,
1.5553,
1.5566,
1.5579,
1.5593,
1.5606,
1.5619,
1.5632,
1.5646,
1.5659,
1.5672,
1.5685,
1.5699,
1.5712,
1.5725,
1.5738,
1.5752,
1.5765,
1.5778,
1.5792,
1.5805,
1.5819,
1.5832,
1.5845,
1.5859,
1.5872,
1.5886,
1.5899,
1.5913,
1.5926,
1.594,
1.5953,
1.5967,
1.598,
1.5994,
1.6007,
1.6021,
1.6034,
1.6048,
1.6061,
1.6075,
1.6089,
1.6102,
1.6116,
1.6129,
1.6143,
1.6157,
1.617,
1.6184,
1.6198,
1.6212,
1.6225,
1.6239,
1.6253,
1.6267,
1.628,
1.6294,
1.6308,
1.6322,
1.6335,
1.6349,
1.6363,
1.6377,
1.6391,
1.6405,
1.6419,
1.6433,
1.6446,
1.646,
1.6474,
1.6488,
1.6502,
1.6516,
1.653,
1.6544,
1.6558,
1.6572,
1.6586,
1.66,
1.6614,
1.6628,
1.6642,
1.6656,
1.6671,
1.6685,
1.6699,
1.6713,
1.6727,
1.6741,
1.6755,
1.677,
1.6784,
1.6798,
1.6812,
1.6826,
1.6841,
1.6855,
1.6869,
1.6884,
1.6898,
1.6912,
1.6926,
1.6941,
1.6955,
1.6969,
1.6984,
1.6998,
1.7013,
1.7027,
1.7041,
1.7056,
1.707,
1.7085,
1.7099,
1.7114,
1.7128,
1.7143,
1.7157,
1.7172,
1.7186,
1.7201,
1.7215,
1.723,
1.7244,
1.7259,
1.7274,
1.7288,
1.7303,
1.7318,
1.7332,
1.7347,
1.7362,
1.7376,
1.7391,
1.7406,
1.742,
1.7435,
1.745,
1.7465,
1.748,
1.7494,
1.7509,
1.7524,
1.7539,
1.7554,
1.7568,
1.7583,
1.7598,
1.7613,
1.7628,
1.7643,
1.7658,
1.7673,
1.7688,
1.7703,
1.7718,
1.7733,
1.7748,
1.7763,
1.7778,
1.7793,
1.7808,
1.7823,
1.7838,
1.7853,
1.7868,
1.7883,
1.7899,
1.7914,
1.7929,
1.7944,
1.7959,
1.7974,
1.799,
1.8005,
1.802,
1.8035,
1.8051,
1.8066,
1.8081,
1.8097,
1.8112,
1.8127,
1.8143,
1.8158,
1.8173,
1.8189,
1.8204,
1.8219,
1.8235,
1.825,
1.8266,
1.8281,
1.8297,
1.8312,
1.8328,
1.8343,
1.8359,
1.8374,
1.839,
1.8405,
1.8421,
1.8437,
1.8452,
1.8468,
1.8483,
1.8499,
1.8515,
1.853,
1.8546,
1.8562,
1.8577,
1.8593,
1.8609,
1.8625,
1.864,
1.8656,
1.8672,
1.8688,
1.8704,
1.8719,
1.8735,
1.8751,
1.8767,
1.8783,
1.8799,
1.8815,
1.8831,
1.8847,
1.8863,
1.8879,
1.8895,
1.8911,
1.8927,
1.8943,
1.8959,
1.8975,
1.8991,
1.9007,
1.9023,
1.9039,
1.9055,
1.9071,
1.9087,
1.9104,
1.912,
1.9136,
1.9152,
1.9168,
1.9185,
1.9201,
1.9217,
1.9233,
1.925,
1.9266,
1.9282,
1.9298,
1.9315,
1.9331,
1.9348,
1.9364,
1.938,
1.9397,
1.9413,
1.943,
1.9446,
1.9462,
1.9479,
1.9495,
1.9512,
1.9528,
1.9545,
1.9562,
1.9578,
1.9595,
1.9611,
1.9628,
1.9644,
1.9661,
1.9678,
1.9694,
1.9711,
1.9728,
1.9744,
1.9761,
1.9778,
1.9795,
1.9811,
1.9828,
1.9845,
1.9862,
1.9879,
1.9895,
1.9912,
1.9929,
1.9946,
1.9963,
1.998,
1.9997,
2.0014,
2.003,
2.0047,
2.0064,
2.0081,
2.0098,
2.0115,
2.0132,
2.0149,
2.0167,
2.0184,
2.0201,
2.0218,
2.0235,
2.0252,
2.0269,
2.0286,
2.0304,
2.0321,
2.0338,
2.0355,
2.0372,
2.039,
2.0407,
2.0424,
2.0441,
2.0459,
2.0476,
2.0493,
2.0511,
2.0528,
2.0545,
2.0563,
2.058,
2.0598,
2.0615,
2.0633,
2.065,
2.0667,
2.0685,
2.0702,
2.072,
2.0738,
2.0755,
2.0773,
2.079,
2.0808,
2.0825,
2.0843,
2.0861,
2.0878,
2.0896,
2.0914,
2.0931,
2.0949,
2.0967,
2.0985,
2.1002,
2.102,
2.1038,
2.1056,
2.1074,
2.1091,
2.1109,
2.1127,
2.1145,
2.1163,
2.1181,
2.1199,
2.1217,
2.1235,
2.1253,
2.1271,
2.1289,
2.1307,
2.1325,
2.1343,
2.1361,
2.1379,
2.1397,
2.1415,
2.1433,
2.1451,
2.147,
2.1488,
2.1506,
2.1524,
2.1542,
2.1561,
2.1579,
2.1597,
2.1615,
2.1634,
2.1652,
2.167,
2.1689,
2.1707,
2.1725,
2.1744,
2.1762,
2.1781,
2.1799,
2.1818,
2.1836,
2.1854,
2.1873,
2.1892,
2.191,
2.1929,
2.1947,
2.1966,
2.1984,
2.2003,
2.2022,
2.204,
2.2059,
2.2078,
2.2096,
2.2115,
2.2134,
2.2152,
2.2171,
2.219,
2.2209,
2.2227,
2.2246,
2.2265,
2.2284,
2.2303,
2.2322,
2.2341,
2.236,
2.2378,
2.2397,
2.2416,
2.2435,
2.2454,
2.2473,
2.2492,
2.2511,
2.253,
2.255,
2.2569,
2.2588,
2.2607,
2.2626,
2.2645,
2.2664,
2.2683,
2.2703,
2.2722,
2.2741,
2.276,
2.278,
2.2799,
2.2818,
2.2838,
2.2857,
2.2876,
2.2896,
2.2915,
2.2934,
2.2954,
2.2973,
2.2993,
2.3012,
2.3032,
2.3051,
2.3071,
2.309,
2.311,
2.3129,
2.3149,
2.3168,
2.3188,
2.3208,
2.3227,
2.3247,
2.3267,
2.3286,
2.3306,
2.3326,
2.3346,
2.3365,
2.3385,
2.3405,
2.3425,
2.3444,
2.3464,
2.3484,
2.3504,
2.3524,
2.3544,
2.3564,
2.3584,
2.3604,
2.3624,
2.3644,
2.3664,
2.3684,
2.3704,
2.3724,
2.3744,
2.3764,
2.3784,
2.3804,
2.3824,
2.3845,
2.3865,
2.3885,
2.3905,
2.3925,
2.3946,
2.3966,
2.3986,
2.4007,
2.4027,
2.4047,
2.4068,
2.4088,
2.4108,
2.4129,
2.4149,
2.417,
2.419,
2.4211,
2.4231,
2.4252,
2.4272,
2.4293,
2.4313,
2.4334,
2.4354,
2.4375,
2.4396,
2.4416,
2.4437,
2.4458,
2.4478,
2.4499,
2.452,
2.4541,
2.4561,
2.4582,
2.4603,
2.4624,
2.4645,
2.4665,
2.4686,
2.4707,
2.4728,
2.4749,
2.477,
2.4791,
2.4812,
2.4833,
2.4854,
2.4875,
2.4896,
2.4917,
2.4938,
2.4959,
2.498,
2.5002,
2.5023,
2.5044,
2.5065,
2.5086,
2.5108,
2.5129,
2.515,
2.5171,
2.5193,
2.5214,
2.5235,
2.5257,
2.5278,
2.53,
2.5321,
2.5342,
2.5364,
2.5385,
2.5407,
2.5428,
2.545,
2.5471,
2.5493,
2.5515,
2.5536,
2.5558,
2.5579,
2.5601,
2.5623,
2.5644,
2.5666,
2.5688,
2.571,
2.5731,
2.5753,
2.5775,
2.5797,
2.5819,
2.584,
2.5862,
2.5884,
2.5906,
2.5928,
2.595,
2.5972,
2.5994,
2.6016,
2.6038,
2.606,
2.6082,
2.6104,
2.6126,
2.6148,
2.617,
2.6193,
2.6215,
2.6237,
2.6259,
2.6281,
2.6304,
2.6326,
2.6348,
2.6371,
2.6393,
2.6415,
2.6438,
2.646,
2.6482,
2.6505,
2.6527,
2.655,
2.6572,
2.6595,
2.6617,
2.664,
2.6662,
2.6685,
2.6707,
2.673,
2.6753,
2.6775,
2.6798,
2.6821,
2.6843,
2.6866,
2.6889,
2.6911,
2.6934,
2.6957,
2.698,
2.7003,
2.7026,
2.7048,
2.7071,
2.7094,
2.7117,
2.714,
2.7163,
2.7186,
2.7209,
2.7232,
2.7255,
2.7278,
2.7301,
2.7325,
2.7348,
2.7371,
2.7394,
2.7417,
2.744,
2.7464,
2.7487,
2.751,
2.7533,
2.7557,
2.758,
2.7603,
2.7627,
2.765,
2.7674,
2.7697,
2.772,
2.7744,
2.7767,
2.7791,
2.7814,
2.7838,
2.7861,
2.7885,
2.7909,
2.7932,
2.7956,
2.798,
2.8003,
2.8027,
2.8051,
2.8074,
2.8098,
2.8122,
2.8146,
2.817,
2.8193,
2.8217,
2.8241,
2.8265,
2.8289,
2.8313,
2.8337,
2.8361,
2.8385,
2.8409,
2.8433,
2.8457,
2.8481,
2.8505,
2.8529,
2.8554,
2.8578,
2.8602,
2.8626,
2.865,
2.8675,
2.8699,
2.8723,
2.8748,
2.8772,
2.8796,
2.8821,
2.8845,
2.8869,
2.8894,
2.8918,
2.8943,
2.8967,
2.8992,
2.9016,
2.9041,
2.9065,
2.909,
2.9115,
2.9139,
2.9164,
2.9189,
2.9213,
2.9238,
2.9263,
2.9288,
2.9312,
2.9337,
2.9362,
2.9387,
2.9412,
2.9437,
2.9462,
2.9487,
2.9512,
2.9537,
2.9562,
2.9587,
2.9612,
2.9637,
2.9662,
2.9687,
2.9712,
2.9737,
2.9762,
2.9787,
2.9813,
2.9838,
2.9863,
2.9888,
2.9914,
2.9939,
2.9964,
2.999,
3.0015,
3.0041,
3.0066,
3.0091,
3.0117,
3.0142,
3.0168,
3.0194,
3.0219,
3.0245,
3.027,
3.0296,
3.0322,
3.0347,
3.0373,
3.0399,
3.0424,
3.045,
3.0476,
3.0502,
3.0527,
3.0553,
3.0579,
3.0605,
3.0631,
3.0657,
3.0683,
3.0709,
3.0735,
3.0761,
3.0787,
3.0813,
3.0839,
3.0865,
3.0891,
3.0917,
3.0944,
3.097,
3.0996,
3.1022,
3.1048,
3.1075,
3.1101,
3.1127,
3.1154,
3.118,
3.1206,
3.1233,
3.1259,
3.1286,
3.1312,
3.1339,
3.1365,
3.1392,
3.1418,
3.1445,
3.1472,
3.1498,
3.1525,
3.1552,
3.1578,
3.1605,
3.1632,
3.1659,
3.1685,
3.1712,
3.1739,
3.1766,
3.1793,
3.182,
3.1847,
3.1874,
3.1901,
3.1928,
3.1955,
3.1982,
3.2009,
3.2036,
3.2063,
3.209,
3.2117,
3.2144,
3.2172,
3.2199,
3.2226,
3.2253,
3.2281,
3.2308,
3.2335,
3.2363,
3.239,
3.2418,
3.2445,
3.2473,
3.25,
3.2528,
3.2555,
3.2583,
3.261,
3.2638,
3.2665,
3.2693,
3.2721,
3.2748,
3.2776,
3.2804,
3.2832,
3.2859,
3.2887,
3.2915,
3.2943,
3.2971,
3.2999,
3.3027,
3.3055,
3.3083,
3.3111,
3.3139,
3.3167,
3.3195,
3.3223,
3.3251,
3.3279,
3.3307,
3.3336,
3.3364,
3.3392,
3.342,
3.3449,
3.3477,
3.3505,
3.3534,
3.3562,
3.359,
3.3619,
3.3647,
3.3676,
3.3704,
3.3733,
3.3761,
3.379,
3.3818,
3.3847,
3.3876,
3.3904,
3.3933,
3.3962,
3.3991,
3.4019,
3.4048,
3.4077,
3.4106,
3.4135,
3.4164,
3.4193,
3.4221,
3.425,
3.4279,
3.4308,
3.4338,
3.4367,
3.4396,
3.4425,
3.4454,
3.4483,
3.4512,
3.4541,
3.4571,
3.46,
3.4629,
3.4659,
3.4688,
3.4717,
3.4747,
3.4776,
3.4806,
3.4835,
3.4864,
3.4894,
3.4924,
3.4953,
3.4983,
3.5012,
3.5042,
3.5072,
3.5101,
3.5131,
3.5161,
3.519,
3.522,
3.525,
3.528,
3.531,
3.534,
3.537,
3.54,
3.543,
3.5459,
3.549,
3.552,
3.555,
3.558,
3.561,
3.564,
3.567,
3.57,
3.5731,
3.5761,
3.5791,
3.5821,
3.5852,
3.5882,
3.5912,
3.5943,
3.5973,
3.6004,
3.6034,
3.6065,
3.6095,
3.6126,
3.6156,
3.6187,
3.6218,
3.6248,
3.6279,
3.631,
3.634,
3.6371,
3.6402,
3.6433,
3.6464,
3.6494,
3.6525,
3.6556,
3.6587,
3.6618,
3.6649,
3.668,
3.6711,
3.6742,
3.6773,
3.6805,
3.6836,
3.6867,
3.6898,
3.6929,
3.6961,
3.6992,
3.7023,
3.7054,
3.7086,
3.7117,
3.7149,
3.718,
3.7212,
3.7243,
3.7275,
3.7306,
3.7338,
3.7369,
3.7401,
3.7433,
3.7464,
3.7496,
3.7528,
3.756,
3.7591,
3.7623,
3.7655,
3.7687,
3.7719,
3.7751,
3.7783,
3.7815,
3.7847,
3.7879,
3.7911,
3.7943,
3.7975,
3.8007,
3.8039,
3.8071,
3.8104,
3.8136,
3.8168,
3.8201,
3.8233,
3.8265,
3.8298,
3.833,
3.8363,
3.8395,
3.8427,
3.846,
3.8493,
3.8525,
3.8558,
3.859,
3.8623,
3.8656,
3.8688,
3.8721,
3.8754,
3.8787,
3.882,
3.8853,
3.8885,
3.8918,
3.8951,
3.8984,
3.9017,
3.905,
3.9083,
3.9116,
3.915,
3.9183,
3.9216,
3.9249,
3.9282,
3.9315,
3.9349,
3.9382,
3.9415,
3.9449,
3.9482,
3.9516,
3.9549,
3.9583,
3.9616,
3.965,
3.9683,
3.9717,
3.975,
3.9784,
3.9818,
3.9851,
3.9885,
3.9919,
3.9953,
3.9986,
4.002,
4.0054,
4.0088,
4.0122,
4.0156,
4.019,
4.0224,
4.0258,
4.0292,
4.0326,
4.036,
4.0395,
4.0429,
4.0463,
4.0497,
4.0531,
4.0566,
4.06,
4.0634,
4.0669,
4.0703,
4.0738,
4.0772,
4.0807,
4.0841,
4.0876,
4.091,
4.0945,
4.098,
4.1014,
4.1049,
4.1084,
4.1119,
4.1154,
4.1188,
4.1223,
4.1258,
4.1293,
4.1328,
4.1363,
4.1398,
4.1433,
4.1468,
4.1503,
4.1538,
4.1573,
4.1609,
4.1644,
4.1679,
4.1714,
4.175,
4.1785,
4.182,
4.1856,
4.1891,
4.1927,
4.1962,
4.1998,
4.2033,
4.2069,
4.2105,
4.214,
4.2176,
4.2212,
4.2247,
4.2283,
4.2319,
4.2355,
4.239,
4.2426,
4.2462,
4.2498,
4.2534,
4.257,
4.2606,
4.2642,
4.2678,
4.2715,
4.2751,
4.2787,
4.2823,
4.2859,
4.2896,
4.2932,
4.2968,
4.3005,
4.3041,
4.3077,
4.3114,
4.315,
4.3187,
4.3224,
4.326,
4.3297,
4.3333,
4.337,
4.3407,
4.3444,
4.348,
4.3517,
4.3554,
4.3591,
4.3628,
4.3665,
4.3702,
4.3739,
4.3776,
4.3813,
4.385,
4.3887,
4.3924,
4.3961,
4.3998,
4.4036,
4.4073,
4.411,
4.4148,
4.4185,
4.4222,
4.426,
4.4297,
4.4335,
4.4372,
4.441,
4.4447,
4.4485,
4.4523,
4.456,
4.4598,
4.4636,
4.4674,
4.4711,
4.4749,
4.4787,
4.4825,
4.4863,
4.4901,
4.4939,
4.4977,
4.5015,
4.5053,
4.5091,
4.513,
4.5168,
4.5206,
4.5244,
4.5283,
4.5321,
4.5359,
4.5398,
4.5436,
4.5475,
4.5513,
4.5552,
4.559,
4.5629,
4.5667,
4.5706,
4.5745,
4.5783,
4.5822,
4.5861,
4.59,
4.5939,
4.5977,
4.6016,
4.6055,
4.6094,
4.6133,
4.6172,
4.6212,
4.6251,
4.629,
4.6329,
4.6368,
4.6407,
4.6447,
4.6486,
4.6525,
4.6565,
4.6604,
4.6644,
4.6683,
4.6723,
4.6762,
4.6802,
4.6841,
4.6881,
4.6921,
4.696,
4.7,
4.704,
4.708,
4.712,
4.716,
4.7199,
4.7239,
4.7279,
4.7319,
4.7359,
4.74,
4.744,
4.748,
4.752,
4.756,
4.76,
4.7641,
4.7681,
4.7721,
4.7762,
4.7802,
4.7843,
4.7883,
4.7924,
4.7964,
4.8005,
4.8046,
4.8086,
4.8127,
4.8168,
4.8208,
4.8249,
4.829,
4.8331,
4.8372,
4.8413,
4.8454,
4.8495,
4.8536,
4.8577,
4.8618,
4.8659,
4.87,
4.8742,
4.8783,
4.8824,
4.8866,
4.8907,
4.8948,
4.899,
4.9031,
4.9073,
4.9114,
4.9156,
4.9197,
4.9239,
4.9281,
4.9323,
4.9364,
4.9406,
4.9448,
4.949,
4.9532,
4.9574,
4.9616,
4.9658,
4.97,
4.9742,
4.9784,
4.9826,
4.9868,
4.991,
4.9952,
4.9995,
5.0037,
5.0079,
5.0122,
5.0164,
5.0207,
5.0249,
5.0292,
5.0334,
5.0377,
5.042,
5.0462,
5.0505,
5.0548,
5.0591,
5.0633,
5.0676,
5.0719,
5.0762,
5.0805,
5.0848,
5.0891,
5.0934,
5.0977,
5.102,
5.1064,
5.1107,
5.115,
5.1193,
5.1237,
5.128,
5.1323,
5.1367,
5.141,
5.1454,
5.1497,
5.1541,
5.1585,
5.1628,
5.1672,
5.1716,
5.176,
5.1803,
5.1847,
5.1891,
5.1935,
5.1979,
5.2023,
5.2067,
5.2111,
5.2155,
5.2199,
5.2244,
5.2288,
5.2332,
5.2376,
5.2421,
5.2465,
5.2509,
5.2554,
5.2598,
5.2643,
5.2688,
5.2732,
5.2777,
5.2821,
5.2866,
5.2911,
5.2956,
5.3,
5.3045,
5.309,
5.3135,
5.318,
5.3225,
5.327,
5.3315,
5.336,
5.3406,
5.3451,
5.3496,
5.3541,
5.3587,
5.3632,
5.3677,
5.3723,
5.3768,
5.3814,
5.3859,
5.3905,
5.3951,
5.3996,
5.4042,
5.4088,
5.4134,
5.4179,
5.4225,
5.4271,
5.4317,
5.4363,
5.4409,
5.4455,
5.4501,
5.4547,
5.4594,
5.464,
5.4686,
5.4732,
5.4779,
5.4825,
5.4871,
5.4918,
5.4964,
5.5011,
5.5057,
5.5104,
5.5151,
5.5197,
5.5244,
5.5291,
5.5338,
5.5385,
5.5431,
5.5478,
5.5525,
5.5572,
5.5619,
5.5666,
5.5714,
5.5761,
5.5808,
5.5855,
5.5902,
5.595,
5.5997,
5.6044,
5.6092,
5.6139,
5.6187,
5.6234,
5.6282,
5.633,
5.6377,
5.6425,
5.6473,
5.6521,
5.6569,
5.6616,
5.6664,
5.6712,
5.676,
5.6808,
5.6856,
5.6905,
5.6953,
5.7001,
5.7049,
5.7098,
5.7146,
5.7194,
5.7243,
5.7291,
5.734,
5.7388,
5.7437,
5.7485,
5.7534,
5.7583,
5.7631,
5.768,
5.7729,
5.7778,
5.7827,
5.7876,
5.7925,
5.7974,
5.8023,
5.8072,
5.8121,
5.817,
5.822,
5.8269,
5.8318,
5.8368,
5.8417,
5.8466,
5.8516,
5.8565,
5.8615,
5.8665,
5.8714,
5.8764,
5.8814,
5.8863,
5.8913,
5.8963,
5.9013,
5.9063,
5.9113,
5.9163,
5.9213,
5.9263,
5.9313,
5.9364,
5.9414,
5.9464,
5.9515,
5.9565,
5.9615,
5.9666,
5.9716,
5.9767,
5.9817,
5.9868,
5.9919,
5.9969,
6.002,
6.0071,
6.0122,
6.0173,
6.0224,
6.0275,
6.0326,
6.0377,
6.0428,
6.0479,
6.053,
6.0581,
6.0633,
6.0684,
6.0735,
6.0787,
6.0838,
6.089,
6.0941,
6.0993,
6.1045,
6.1096,
6.1148,
6.12,
6.1252,
6.1303,
6.1355,
6.1407,
6.1459,
6.1511,
6.1563,
6.1615,
6.1668,
6.172,
6.1772,
6.1824,
6.1877,
6.1929,
6.1981,
6.2034,
6.2086,
6.2139,
6.2192,
6.2244,
6.2297,
6.235,
6.2402,
6.2455,
6.2508,
6.2561,
6.2614,
6.2667,
6.272,
6.2773,
6.2826,
6.2879,
6.2933,
6.2986,
6.3039,
6.3093,
6.3146,
6.3199,
6.3253,
6.3306,
6.336,
6.3414,
6.3467,
6.3521,
6.3575,
6.3629,
6.3683,
6.3736,
6.379,
6.3844,
6.3898,
6.3953,
6.4007,
6.4061,
6.4115,
6.4169,
6.4224,
6.4278,
6.4332,
6.4387,
6.4441,
6.4496,
6.4551,
6.4605,
6.466,
6.4715,
6.4769,
6.4824,
6.4879,
6.4934,
6.4989,
6.5044,
6.5099,
6.5154,
6.5209,
6.5265,
6.532,
6.5375,
6.543,
6.5486,
6.5541,
6.5597,
6.5652,
6.5708,
6.5763,
6.5819,
6.5875,
6.5931,
6.5986,
6.6042,
6.6098,
6.6154,
6.621,
6.6266,
6.6322,
6.6378,
6.6435,
6.6491,
6.6547,
6.6603,
6.666,
6.6716,
6.6773,
6.6829,
6.6886,
6.6942,
6.6999,
6.7056,
6.7113,
6.7169,
6.7226,
6.7283,
6.734,
6.7397,
6.7454,
6.7511,
6.7568,
6.7626,
6.7683,
6.774,
6.7797,
6.7855,
6.7912,
6.797,
6.8027,
6.8085,
6.8142,
6.82,
6.8258,
6.8316,
6.8374,
6.8431,
6.8489,
6.8547,
6.8605,
6.8663,
6.8722,
6.878,
6.8838,
6.8896,
6.8954,
6.9013,
6.9071,
6.913,
6.9188,
6.9247,
6.9305,
6.9364,
6.9423,
6.9482,
6.954,
6.9599,
6.9658,
6.9717,
6.9776,
6.9835,
6.9894,
6.9954,
7.0013,
7.0072,
7.0131,
7.0191,
7.025,
7.031,
7.0369,
7.0429,
7.0488,
7.0548,
7.0608,
7.0667,
7.0727,
7.0787,
7.0847,
7.0907,
7.0967,
7.1027,
7.1087,
7.1147,
7.1208,
7.1268,
7.1328,
7.1389,
7.1449,
7.1509,
7.157,
7.1631,
7.1691,
7.1752,
7.1813,
7.1873,
7.1934,
7.1995,
7.2056,
7.2117,
7.2178,
7.2239,
7.23,
7.2362,
7.2423,
7.2484,
7.2546,
7.2607,
7.2668,
7.273,
7.2791,
7.2853,
7.2915,
7.2976,
7.3038,
7.31,
7.3162,
7.3224,
7.3286,
7.3348,
7.341,
7.3472,
7.3534,
7.3597,
7.3659,
7.3721,
7.3784,
7.3846,
7.3909,
7.3971,
7.4034,
7.4096,
7.4159,
7.4222,
7.4285,
7.4348,
7.4411,
7.4474,
7.4537,
7.46,
7.4663,
7.4726,
7.4789,
7.4853,
7.4916,
7.4979,
7.5043,
7.5106,
7.517,
7.5234,
7.5297,
7.5361,
7.5425,
7.5489,
7.5553,
7.5617,
7.5681,
7.5745,
7.5809,
7.5873,
7.5937,
7.6001,
7.6066,
7.613,
7.6195,
7.6259,
7.6324,
7.6388,
7.6453,
7.6518,
7.6582,
7.6647,
7.6712,
7.6777,
7.6842,
7.6907,
7.6972,
7.7037,
7.7102,
7.7168,
7.7233,
7.7298,
7.7364,
7.7429,
7.7495,
7.7561,
7.7626,
7.7692,
7.7758,
7.7823,
7.7889,
7.7955,
7.8021,
7.8087,
7.8153,
7.822,
7.8286,
7.8352,
7.8418,
7.8485,
7.8551,
7.8618,
7.8684,
7.8751,
7.8817,
7.8884,
7.8951,
7.9018,
7.9085,
7.9152,
7.9219,
7.9286,
7.9353,
7.942,
7.9487,
7.9554,
7.9622,
7.9689,
7.9757,
7.9824,
7.9892,
7.9959,
8.0027,
8.0095,
8.0163,
8.023,
8.0298,
8.0366,
8.0434,
8.0502,
8.0571,
8.0639,
8.0707,
8.0775,
8.0844,
8.0912,
8.0981,
8.1049,
8.1118,
8.1187,
8.1255,
8.1324,
8.1393,
8.1462,
8.1531,
8.16,
8.1669,
8.1738,
8.1807,
8.1876,
8.1946,
8.2015,
8.2084,
8.2154,
8.2223,
8.2293,
8.2363,
8.2432,
8.2502,
8.2572,
8.2642,
8.2712,
8.2782,
8.2852,
8.2922,
8.2992,
8.3063,
8.3133,
8.3203,
8.3274,
8.3344,
8.3415,
8.3485,
8.3556,
8.3627,
8.3698,
8.3768,
8.3839,
8.391,
8.3981,
8.4052,
8.4124,
8.4195,
8.4266,
8.4337,
8.4409,
8.448,
8.4552,
8.4623,
8.4695,
8.4767,
8.4838,
8.491,
8.4982,
8.5054,
8.5126,
8.5198,
8.527,
8.5342,
8.5415,
8.5487,
8.5559,
8.5632,
8.5704,
8.5777,
8.5849,
8.5922,
8.5995,
8.6068,
8.614,
8.6213,
8.6286,
8.6359,
8.6432,
8.6506,
8.6579,
8.6652,
8.6725,
8.6799,
8.6872,
8.6946,
8.7019,
8.7093,
8.7167,
8.7241,
8.7314,
8.7388,
8.7462,
8.7536,
8.761,
8.7685,
8.7759,
8.7833,
8.7908,
8.7982,
8.8056,
8.8131,
8.8206,
8.828,
8.8355,
8.843,
8.8505,
8.8579,
8.8654,
8.873,
8.8805,
8.888,
8.8955,
8.903,
8.9106,
8.9181,
8.9257,
8.9332,
8.9408,
8.9483,
8.9559,
8.9635,
8.9711,
8.9787,
8.9863,
8.9939,
9.0015,
9.0091,
9.0167,
9.0244,
9.032,
9.0397,
9.0473,
9.055,
9.0626,
9.0703,
9.078,
9.0857,
9.0934,
9.1011,
9.1088,
9.1165,
9.1242,
9.1319,
9.1396,
9.1474,
9.1551,
9.1629,
9.1706,
9.1784,
9.1862,
9.1939,
9.2017,
9.2095,
9.2173,
9.2251,
9.2329,
9.2407,
9.2486,
9.2564,
9.2642,
9.2721,
9.2799,
9.2878,
9.2956,
9.3035,
9.3114,
9.3193,
9.3271,
9.335,
9.3429,
9.3509,
9.3588,
9.3667,
9.3746,
9.3826,
9.3905,
9.3984,
9.4064,
9.4144,
9.4223,
9.4303,
9.4383,
9.4463,
9.4543,
9.4623,
9.4703,
9.4783,
9.4863,
9.4944,
9.5024,
9.5104,
9.5185,
9.5265,
9.5346,
9.5427,
9.5508,
9.5588,
9.5669,
9.575,
9.5831,
9.5912,
9.5994,
9.6075,
9.6156,
9.6238,
9.6319,
9.6401,
9.6482,
9.6564,
9.6646,
9.6727,
9.6809,
9.6891,
9.6973,
9.7055,
9.7138,
9.722,
9.7302,
9.7384,
9.7467,
9.7549,
9.7632,
9.7715,
9.7797,
9.788,
9.7963,
9.8046,
9.8129,
9.8212,
9.8295,
9.8378,
9.8462,
9.8545,
9.8628,
9.8712,
9.8795,
9.8879,
9.8963,
9.9046,
9.913,
9.9214,
9.9298,
9.9382,
9.9466,
9.9551,
9.9635,
9.9719,
9.9804,
9.9888,
9.9973,
10.0057,
10.0142,
10.0227,
10.0312,
10.0396,
10.0481,
10.0567,
10.0652,
10.0737,
10.0822,
10.0907,
10.0993,
10.1078,
10.1164,
10.125,
10.1335,
10.1421,
10.1507,
10.1593,
10.1679,
10.1765,
10.1851,
10.1937,
10.2024,
10.211,
10.2196,
10.2283,
10.2369,
10.2456,
10.2543,
10.263,
10.2716,
10.2803,
10.289,
10.2978,
10.3065,
10.3152,
10.3239,
10.3327,
10.3414,
10.3502,
10.3589,
10.3677,
10.3765,
10.3853,
10.394,
10.4028,
10.4117,
10.4205,
10.4293,
10.4381,
10.4469,
10.4558,
10.4646,
10.4735,
10.4824,
10.4912,
10.5001,
10.509,
10.5179,
10.5268,
10.5357,
10.5446,
10.5536,
10.5625,
10.5714,
10.5804,
10.5893,
10.5983,
10.6073,
10.6163,
10.6252,
10.6342,
10.6432,
10.6522,
10.6613,
10.6703,
10.6793,
10.6884,
10.6974,
10.7065,
10.7155,
10.7246,
10.7337,
10.7428,
10.7519,
10.761,
10.7701,
10.7792,
10.7883,
10.7974,
10.8066,
10.8157,
10.8249,
10.834,
10.8432,
10.8524,
10.8616,
10.8708,
10.88,
10.8892,
10.8984,
10.9076,
10.9169,
10.9261,
10.9354,
10.9446,
10.9539,
10.9631,
10.9724,
10.9817,
10.991,
11.0003,
11.0096,
11.0189,
11.0283,
11.0376,
11.0469,
11.0563,
11.0657,
11.075,
11.0844,
11.0938,
11.1032,
11.1126,
11.122,
11.1314,
11.1408,
11.1502,
11.1597,
11.1691,
11.1786,
11.1881,
11.1975,
11.207,
11.2165,
11.226,
11.2355,
11.245,
11.2545,
11.264,
11.2736,
11.2831,
11.2927,
11.3022,
11.3118,
11.3214,
11.331,
11.3405,
11.3501,
11.3598,
11.3694,
11.379,
11.3886,
11.3983,
11.4079,
11.4176,
11.4272,
11.4369,
11.4466,
11.4563,
11.466,
11.4757,
11.4854,
11.4951,
11.5048,
11.5146,
11.5243,
11.5341,
11.5439,
11.5536,
11.5634,
11.5732,
11.583,
11.5928,
11.6026,
11.6124,
11.6223,
11.6321,
11.6419,
11.6518,
11.6617,
11.6715,
11.6814,
11.6913,
11.7012,
11.7111,
11.721,
11.7309,
11.7409,
11.7508,
11.7608,
11.7707,
11.7807,
11.7906,
11.8006,
11.8106,
11.8206,
11.8306,
11.8406,
11.8507,
11.8607,
11.8707,
11.8808,
11.8908,
11.9009,
11.911,
11.9211,
11.9311,
11.9412,
11.9513,
11.9615,
11.9716,
11.9817,
11.9919,
12.002,
12.0122,
12.0223,
12.0325,
12.0427,
12.0529,
12.0631,
12.0733,
12.0835,
12.0938,
12.104,
12.1142,
12.1245,
12.1348,
12.145,
12.1553,
12.1656,
12.1759,
12.1862,
12.1965,
12.2069,
12.2172,
12.2275,
12.2379,
12.2482,
12.2586,
12.269,
12.2794,
12.2898,
12.3002,
12.3106,
12.321,
12.3314,
12.3419,
12.3523,
12.3628,
12.3732,
12.3837,
12.3942,
12.4047,
12.4152,
12.4257,
12.4362,
12.4467,
12.4573,
12.4678,
12.4784,
12.4889,
12.4995,
12.5101,
12.5207,
12.5313,
12.5419,
12.5525,
12.5631,
12.5738,
12.5844,
12.5951,
12.6057,
12.6164,
12.6271,
12.6378,
12.6484,
12.6592,
12.6699,
12.6806,
12.6913,
12.7021,
12.7128,
12.7236,
12.7344,
12.7451,
12.7559,
12.7667,
12.7775,
12.7883,
12.7992,
12.81,
12.8208,
12.8317,
12.8426,
12.8534,
12.8643,
12.8752,
12.8861,
12.897,
12.9079,
12.9189,
12.9298,
12.9407,
12.9517,
12.9627,
12.9736,
12.9846,
12.9956,
13.0066,
13.0176,
13.0286,
13.0397,
13.0507,
13.0617,
13.0728,
13.0839,
13.0949,
13.106,
13.1171,
13.1282,
13.1393,
13.1505,
13.1616,
13.1727,
13.1839,
13.195,
13.2062,
13.2174,
13.2286,
13.2398,
13.251,
13.2622,
13.2734,
13.2847,
13.2959,
13.3072,
13.3184,
13.3297,
13.341,
13.3523,
13.3636,
13.3749,
13.3862,
13.3975,
13.4089,
13.4202,
13.4316,
13.443,
13.4543,
13.4657,
13.4771,
13.4885,
13.5,
13.5114,
13.5228,
13.5343,
13.5457,
13.5572,
13.5687,
13.5802,
13.5916,
13.6032,
13.6147,
13.6262,
13.6377,
13.6493,
13.6608,
13.6724,
13.684,
13.6955,
13.7071,
13.7187,
13.7304,
13.742,
13.7536,
13.7653,
13.7769,
13.7886,
13.8002,
13.8119,
13.8236,
13.8353,
13.847,
13.8587,
13.8705,
13.8822,
13.894,
13.9057,
13.9175,
13.9293,
13.9411,
13.9529,
13.9647,
13.9765,
13.9883,
14.0002,
14.012,
14.0239,
14.0358,
14.0476,
14.0595,
14.0714,
14.0833,
14.0953,
14.1072,
14.1191,
14.1311,
14.1431,
14.155,
14.167,
14.179,
14.191,
14.203,
14.215,
14.2271,
14.2391,
14.2512,
14.2632,
14.2753,
14.2874,
14.2995,
14.3116,
14.3237,
14.3358,
14.348,
14.3601,
14.3723,
14.3844,
14.3966,
14.4088,
14.421,
14.4332,
14.4454,
14.4576,
14.4699,
14.4821,
14.4944,
14.5067,
14.5189,
14.5312,
14.5435,
14.5558,
14.5682,
14.5805,
14.5928,
14.6052,
14.6175,
14.6299,
14.6423,
14.6547,
14.6671,
14.6795,
14.6919,
14.7044,
14.7168,
14.7293,
14.7418,
14.7542,
14.7667,
14.7792,
14.7917,
14.8042,
14.8168,
14.8293,
14.8419,
14.8544,
14.867,
14.8796,
14.8922,
14.9048,
14.9174,
14.93,
14.9427,
14.9553,
14.968,
14.9807,
14.9933,
15.006,
15.0187,
15.0314,
15.0442,
15.0569,
15.0697,
15.0824,
15.0952,
15.108,
15.1207,
15.1335,
15.1464,
15.1592,
15.172,
15.1848,
15.1977,
15.2106,
15.2234,
15.2363,
15.2492,
15.2621,
15.2751,
15.288,
15.3009,
15.3139,
15.3268,
15.3398,
15.3528,
15.3658,
15.3788,
15.3918,
15.4048,
15.4179,
15.4309,
15.444,
15.4571,
15.4702,
15.4833,
15.4964,
15.5095,
15.5226,
15.5357,
15.5489,
15.5621,
15.5752,
15.5884,
15.6016,
15.6148,
15.628,
15.6413,
15.6545,
15.6678,
15.681,
15.6943,
15.7076,
15.7209,
15.7342,
15.7475,
15.7608,
15.7742,
15.7875,
15.8009,
15.8143,
15.8276,
15.841,
15.8545,
15.8679,
15.8813,
15.8948,
15.9082,
15.9217,
15.9351,
15.9486,
15.9621,
15.9757,
15.9892,
16.0027,
16.0163,
16.0298,
16.0434,
16.057,
16.0706,
16.0842,
16.0978,
16.1114,
16.125,
16.1387,
16.1523,
16.166,
16.1797,
16.1934,
16.2071,
16.2208,
16.2346,
16.2483,
16.2621,
16.2758,
16.2896,
16.3034,
16.3172,
16.331,
16.3448,
16.3587,
16.3725,
16.3864,
16.4002,
16.4141,
16.428,
16.4419,
16.4558,
16.4698,
16.4837,
16.4977,
16.5116,
16.5256,
16.5396,
16.5536,
16.5676,
16.5816,
16.5957,
16.6097,
16.6238,
16.6378,
16.6519,
16.666,
16.6801,
16.6942,
16.7084,
16.7225,
16.7367,
16.7508,
16.765,
16.7792,
16.7934,
16.8076,
16.8219,
16.8361,
16.8504,
16.8646,
16.8789,
16.8932,
16.9075,
16.9218,
16.9361,
16.9505,
16.9648,
16.9792,
16.9935,
17.0079,
17.0223,
17.0367,
17.0511,
17.0656,
17.08,
17.0945,
17.109,
17.1234,
17.1379,
17.1524,
17.167,
17.1815,
17.196,
17.2106,
17.2252,
17.2397,
17.2543,
17.2689,
17.2836,
17.2982,
17.3128,
17.3275,
17.3422,
17.3568,
17.3715,
17.3862,
17.4009,
17.4157,
17.4304,
17.4452,
17.4599,
17.4747,
17.4895,
17.5043,
17.5191,
17.534,
17.5488,
17.5637,
17.5785,
17.5934,
17.6083,
17.6232,
17.6381,
17.6531,
17.668,
17.683,
17.6979,
17.7129,
17.7279,
17.7429,
17.7579,
17.773,
17.788,
17.8031,
17.8181,
17.8332,
17.8483,
17.8634,
17.8785,
17.8937,
17.9088,
17.924,
17.9391,
17.9543,
17.9695,
17.9847,
18.0,
18.0152,
18.0304,
18.0457,
18.061,
18.0763,
18.0916,
18.1069,
18.1222,
18.1376,
18.1529,
18.1683,
18.1837,
18.199,
18.2145,
18.2299,
18.2453,
18.2607,
18.2762,
18.2917,
18.3072,
18.3227,
18.3382,
18.3537,
18.3692,
18.3848,
18.4003,
18.4159,
18.4315,
18.4471,
18.4627,
18.4783,
18.494,
18.5096,
18.5253,
18.541,
18.5567,
18.5724,
18.5881,
18.6038,
18.6196,
18.6354,
18.6511,
18.6669,
18.6827,
18.6985,
18.7144,
18.7302,
18.7461,
18.7619,
18.7778,
18.7937,
18.8096,
18.8255,
18.8415,
18.8574,
18.8734,
18.8894,
18.9054,
18.9214,
18.9374,
18.9534,
18.9694,
18.9855,
19.0016,
19.0177,
19.0338,
19.0499,
19.066,
19.0821,
19.0983,
19.1145,
19.1306,
19.1468,
19.163,
19.1793,
19.1955,
19.2117,
19.228,
19.2443,
19.2606,
19.2769,
19.2932,
19.3095,
19.3259,
19.3422,
19.3586,
19.375,
19.3914,
19.4078,
19.4242,
19.4407,
19.4571,
19.4736,
19.4901,
19.5066,
19.5231,
19.5396,
19.5562,
19.5727,
19.5893,
19.6059,
19.6225,
19.6391,
19.6557,
19.6723,
19.689,
19.7056,
19.7223,
19.739,
19.7557,
19.7725,
19.7892,
19.8059,
19.8227,
19.8395,
19.8563,
19.8731,
19.8899,
19.9067,
19.9236,
19.9405,
19.9573,
19.9742,
19.9911,
20.0081,
20.025,
20.042,
20.0589,
20.0759,
20.0929,
20.1099,
20.1269,
20.144,
20.161,
20.1781,
20.1952,
20.2123,
20.2294,
20.2465,
20.2636,
20.2808,
20.2979,
20.3151,
20.3323,
20.3495,
20.3668,
20.384,
20.4013,
20.4185,
20.4358,
20.4531,
20.4704,
20.4877,
20.5051,
20.5224,
20.5398,
20.5572,
20.5746,
20.592,
20.6095,
20.6269,
20.6444,
20.6618,
20.6793,
20.6968,
20.7143,
20.7319,
20.7494,
20.767,
20.7846,
20.8022,
20.8198,
20.8374,
20.855,
20.8727,
20.8904,
20.908,
20.9257,
20.9435,
20.9612,
20.9789,
20.9967,
21.0145,
21.0322,
21.0501,
21.0679,
21.0857,
21.1036,
21.1214,
21.1393,
21.1572,
21.1751,
21.193,
21.211,
21.2289,
21.2469,
21.2649,
21.2829,
21.3009,
21.3189,
21.337,
21.355,
21.3731,
21.3912,
21.4093,
21.4274,
21.4456,
21.4637,
21.4819,
21.5001,
21.5183,
21.5365,
21.5547,
21.573,
21.5912,
21.6095,
21.6278,
21.6461,
21.6644,
21.6828,
21.7011,
21.7195,
21.7379,
21.7563,
21.7747,
21.7931,
21.8116,
21.83,
21.8485,
21.867,
21.8855,
21.904,
21.9226,
21.9411,
21.9597,
21.9783,
21.9969,
22.0155,
22.0342,
22.0528,
22.0715,
22.0902,
22.1089,
22.1276,
22.1463,
22.1651,
22.1838,
22.2026,
22.2214,
22.2402,
22.259,
22.2779,
22.2967,
22.3156,
22.3345,
22.3534,
22.3723,
22.3913,
22.4102,
22.4292,
22.4482,
22.4672,
22.4862,
22.5052,
22.5243,
22.5433,
22.5624,
22.5815,
22.6006,
22.6198,
22.6389,
22.6581,
22.6773,
22.6964,
22.7157,
22.7349,
22.7541,
22.7734,
22.7927,
22.812,
22.8313,
22.8506,
22.8699,
22.8893,
22.9087,
22.9281,
22.9475,
22.9669,
22.9863,
23.0058,
23.0253,
23.0448,
23.0643,
23.0838,
23.1033,
23.1229,
23.1425,
23.1621,
23.1817,
23.2013,
23.2209,
23.2406,
23.2603,
23.2799,
23.2996,
23.3194,
23.3391,
23.3589,
23.3786,
23.3984,
23.4182,
23.4381,
23.4579,
23.4778,
23.4976,
23.5175,
23.5374,
23.5574,
23.5773,
23.5973,
23.6172,
23.6372,
23.6572,
23.6773,
23.6973,
23.7174,
23.7374,
23.7575,
23.7776,
23.7978,
23.8179,
23.8381,
23.8582,
23.8784,
23.8987,
23.9189,
23.9391,
23.9594,
23.9797,
24.0,
24.0203,
24.0406,
24.061,
24.0813,
24.1017,
24.1221,
24.1425,
24.163,
24.1834,
24.2039,
24.2244,
24.2449,
24.2654,
24.286,
24.3065,
24.3271,
24.3477,
24.3683,
24.3889,
24.4096,
24.4302,
24.4509,
24.4716,
24.4923,
24.5131,
24.5338,
24.5546,
24.5754,
24.5962,
24.617,
24.6378,
24.6587,
24.6795,
24.7004,
24.7213,
24.7423,
24.7632,
24.7842,
24.8052,
24.8262,
24.8472,
24.8682,
24.8893,
24.9103,
24.9314,
24.9525,
24.9736,
24.9948,
25.0159,
25.0371,
25.0583,
25.0795,
25.1007,
25.122,
25.1433,
25.1645,
25.1858,
25.2072,
25.2285,
25.2499,
25.2712,
25.2926,
25.314,
25.3355,
25.3569,
25.3784,
25.3998,
25.4214,
25.4429,
25.4644,
25.486,
25.5075,
25.5291,
25.5507,
25.5724,
25.594,
25.6157,
25.6374,
25.6591,
25.6808,
25.7025,
25.7243,
25.7461,
25.7678,
25.7897,
25.8115,
25.8333,
25.8552,
25.8771,
25.899,
25.9209,
25.9429,
25.9648,
25.9868,
26.0088,
26.0308,
26.0528,
26.0749,
26.097,
26.1191,
26.1412,
26.1633,
26.1854,
26.2076,
26.2298,
26.252,
26.2742,
26.2965,
26.3187,
26.341,
26.3633,
26.3856,
26.4079,
26.4303,
26.4527,
26.4751,
26.4975,
26.5199,
26.5424,
26.5648,
26.5873,
26.6098,
26.6323,
26.6549,
26.6774,
26.7,
26.7226,
26.7453,
26.7679,
26.7906,
26.8132,
26.8359,
26.8586,
26.8814,
26.9041,
26.9269,
26.9497,
26.9725,
26.9953,
27.0182,
27.0411,
27.064,
27.0869,
27.1098,
27.1327,
27.1557,
27.1787,
27.2017,
27.2247,
27.2478,
27.2708,
27.2939,
27.317,
27.3401,
27.3633,
27.3865,
27.4096,
27.4328,
27.4561,
27.4793,
27.5026,
27.5258,
27.5491,
27.5725,
27.5958,
27.6192,
27.6425,
27.6659,
27.6894,
27.7128,
27.7363,
27.7597,
27.7832,
27.8068,
27.8303,
27.8538,
27.8774,
27.901,
27.9246,
27.9483,
27.9719,
27.9956,
28.0193,
28.043,
28.0668,
28.0905,
28.1143,
28.1381,
28.1619,
28.1858,
28.2096,
28.2335,
28.2574,
28.2813,
28.3053,
28.3292,
28.3532,
28.3772,
28.4012,
28.4253,
28.4493,
28.4734,
28.4975,
28.5216,
28.5458,
28.5699,
28.5941,
28.6183,
28.6425,
28.6668,
28.6911,
28.7153,
28.7397,
28.764,
28.7883,
28.8127,
28.8371,
28.8615,
28.8859,
28.9104,
28.9349,
28.9593,
28.9839,
29.0084,
29.0329,
29.0575,
29.0821,
29.1067,
29.1314,
29.156,
29.1807,
29.2054,
29.2301,
29.2549,
29.2796,
29.3044,
29.3292,
29.3541,
29.3789,
29.4038,
29.4287,
29.4536,
29.4785,
29.5035,
29.5284,
29.5534,
29.5785,
29.6035,
29.6285,
29.6536,
29.6787,
29.7039,
29.729,
29.7542,
29.7793,
29.8046,
29.8298,
29.855,
29.8803,
29.9056,
29.9309,
29.9563,
29.9816,
30.007,
30.0324,
30.0578,
30.0833,
30.1087,
30.1342,
30.1597,
30.1852,
30.2108,
30.2364,
30.262,
30.2876,
30.3132,
30.3389,
30.3646,
30.3903,
30.416,
30.4417,
30.4675,
30.4933,
30.5191,
30.5449,
30.5708,
30.5967,
30.6226,
30.6485,
30.6744,
30.7004,
30.7264,
30.7524,
30.7784,
30.8045,
30.8306,
30.8567,
30.8828,
30.9089,
30.9351,
30.9613,
30.9875,
31.0137,
31.04,
31.0662,
31.0925,
31.1188,
31.1452,
31.1716,
31.1979,
31.2243,
31.2508,
31.2772,
31.3037,
31.3302,
31.3567,
31.3833,
31.4098,
31.4364,
31.463,
31.4897,
31.5163,
31.543,
31.5697,
31.5964,
31.6232,
31.6499,
31.6767,
31.7035,
31.7304,
31.7572,
31.7841,
31.811,
31.838,
31.8649,
31.8919,
31.9189,
31.9459,
31.9729,
};
