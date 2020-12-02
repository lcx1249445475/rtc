/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "modules/audio_coding/codecs/isac/fix/source/codec.h"
#include "system_wrappers/include/cpu_features_wrapper.h"
#include "test/gtest.h"

static const int kSamples = FRAMESAMPLES / 2;
static const int32_t spec2time_out_expected_1[kSamples] = {
    -3366470, -2285227, -3415765,  -2310215, -3118030,  -2222470, -3030254,
    -2192091, -3423170, -2216041,  -3305541, -2171936,  -3195767, -2095779,
    -3153304, -2157560, -3071167,  -2032108, -3101190,  -1972016, -3103824,
    -2089118, -3139811, -1898337,  -3102801, -2055082,  -3029665, -1854140,
    -2962586, -1966454, -3071167,  -1894588, -2851743,  -1917315, -2848087,
    -1594932, -2799242, -1462184,  -2845887, -1437599,  -2691776, -1329637,
    -2770659, -1268491, -2625161,  -1578991, -2460299,  -1186385, -2365613,
    -1039354, -2322608, -958518,   -2271749, -789860,   -2254538, -850308,
    -2384436, -850959,  -2133734,  -587678,  -2093316,  -495115,  -1973364,
    -475177,  -1801282, -173507,   -1848516, -158015,   -1792018, -62648,
    -1643313, 214746,   -1500758,  267077,   -1450193,  560521,   -1521579,
    675283,   -1345408, 857559,    -1300822, 1116332,   -1294533, 1241117,
    -1070027, 1263503,  -983816,   1529821,  -1019586,  1910421,  -955420,
    2073688,  -836459,  2401105,   -653905,  2690474,   -731425,  2930131,
    -935234,  3299500,  -875978,   3523432,  -878906,   3924822,  -1081630,
    4561267,  -1203023, 5105274,   -1510983, 6052762,   -2294646, 7021597,
    -3108053, 8826736,  -4935222,  11678789, -8442713,  18725700, -21526692,
    25420577, 19589811, -28108666, 12634054, -14483066, 6263217,  -9979706,
    3665661,  -7909736, 2531530,   -6434896, 1700772,   -5525393, 1479473,
    -4894262, 1231760,  -4353044,  1032940,  -3786590,  941152,   -3331614,
    665090,   -2851619, 830696,    -2762201, 958007,    -2483118, 788233,
    -2184965, 804825,   -1967306,  1007255,  -1862474,  920889,   -1457506,
    755406,   -1405841, 890230,    -1302124, 1161599,   -701867,  1154163,
    -1083366, 1204743,  -513581,   1547264,  -650636,   1493384,  -285543,
    1771863,  -277906,  1841343,   -9078,    1751863,   230222,   1819578,
    207170,   1978972,  398137,    2106468,  552155,    1997624,  685213,
    2129520,  601078,   2238736,   944591,   2441879,   1194178,  2355280,
    986124,   2393328,  1049005,   2417944,  1208368,   2489516,  1352023,
    2572118,  1445283,  2856081,   1532997,  2742279,   1615877,  2915274,
    1808036,  2856871,  1806936,   3241747,  1622461,   2978558,  1841297,
    3010378,  1923666,  3271367,   2126700,  3070935,   1956958,  3107588,
    2128405,  3288872,  2114911,   3315952,  2406651,   3344038,  2370199,
    3368980,  2144361,  3305030,   2183803,  3401450,   2523102,  3405463,
    2452475,  3463355,  2421678,   3551968,  2431949,   3477251,  2148125,
    3244489,  2174090};
static const int32_t spec2time_out_expected_2[kSamples] = {
    1691694,   -2499988, -2035547,  1060469,   988634,    -2044502, -306271,
    2041000,   201454,   -2289456,  93694,     2129427,   -369152,  -1887834,
    860796,    2089102,  -929424,   -1673956,  1395291,   1785651,  -1619673,
    -1380109,  1963449,  1093311,   -2111007,  -840456,   2372786,  578119,
    -2242702,  89774,    2463304,   -132717,   -2121480,  643634,   2277636,
    -1125999,  -1995858, 1543748,   2227861,   -1483779,  -1495491, 2102642,
    1833876,   -1920568, -958378,   2485101,   772261,    -2454257, -24942,
    2918714,   136838,   -2500453,  816118,    3039735,   -746560,  -2365815,
    1586396,   2714951,  -1511696,  -1942334,  2571792,   2182827,  -2325335,
    -1311543,  3055970,  1367220,   -2737182,  -110626,   3889222,  631008,
    -3280879,  853066,   4122279,   -706638,   -3334449,  2148311,  3993512,
    -1846301,  -3004894, 3426779,   3329522,   -3165264,  -2242423, 4756866,
    2557711,   -4131280, -805259,   5702711,   1120592,   -4852821, 743664,
    6476444,   -621186,  -5465828,  2815787,   6768835,   -3017442, -5338409,
    5658126,   6838454,  -5492288,  -4682382,  8874947,   6153814,  -8832561,
    -2649251,  12817398, 4237692,   -13000247, 1190661,   18986363, -115738,
    -19693978, 9908367,  30660381,  -10632635, -37962068, 47022884, 89744622,
    -42087632, 40279224, -88869341, -47542383, 38572364,  10441576, -30339718,
    -9926740,  19896578, 28009,     -18886612, -1124047,  13232498, -4150304,
    -12770551, 2637074,  9051831,   -6162211,  -8713972,  4557937,  5489716,
    -6862312,  -5532349, 5415449,   2791310,   -6999367,  -2790102, 5375806,
    546222,    -6486452, -821261,   4994973,   -1278840,  -5645501, 1060484,
    3996285,   -2503954, -4653629,  2220549,   3036977,   -3282133, -3318585,
    2780636,   1789880,  -4004589,  -2041031,  3105373,   574819,   -3992722,
    -971004,   3001703,  -676739,   -3841508,  417284,    2897970,  -1427018,
    -3058480,  1189948,  2210960,   -2268992,  -2603272,  1949785,  1576172,
    -2720404,  -1891738, 2309456,   769178,    -2975646,  -707150,  2424652,
    -88039,    -2966660, -65452,    2320780,   -957557,   -2798978, 744640,
    1879794,   -1672081, -2365319,  1253309,   1366383,   -2204082, -1544367,
    1801452,   613828,   -2531994,  -983847,   2064842,   118326,   -2613790,
    -203220,   2219635,  -730341,   -2641861,  563557,    1765434,  -1329916,
    -2272927,  1037138,  1266725,   -1939220,  -1588643,  1754528,  816552,
    -2376303,  -1099167, 1864999,   122477,    -2422762,  -400027,  1889228,
    -579916,   -2490353, 287139,    2011318,   -1176657,  -2502978, 812896,
    1116502,   -1940211};
static const int16_t time2spec_out_expected_1[kSamples] = {
    20342, 23889, -10063, -9419, 3242,  7280,  -2012, -5029, 332,   4478,
    -97,   -3244, -891,   3117,  773,   -2204, -1335, 2009,  1236,  -1469,
    -1562, 1277,  1366,   -815,  -1619, 599,   1449,  -177,  -1507, 116,
    1294,  263,   -1338,  -244,  1059,  553,   -1045, -549,  829,   826,
    -731,  -755,  516,    909,   -427,  -853,  189,   1004,  -184,  -828,
    -108,  888,   72,     -700,  -280,  717,   342,   -611,  -534,  601,
    534,   -374,  -646,   399,   567,   -171,  -720,  234,   645,   -11,
    -712,  -26,   593,    215,   -643,  -172,  536,   361,   -527,  -403,
    388,   550,   -361,   -480,  208,   623,   -206,  -585,  41,    578,
    12,    -504,  -182,   583,   218,   -437,  -339,  499,   263,   -354,
    -450,  347,   456,    -193,  -524,  212,   475,   -74,   -566,  94,
    511,   112,   -577,   -201,  408,   217,   -546,  -295,  338,   387,
    -13,   4,     -46,    2,     -76,   103,   -83,   108,   -55,   100,
    -150,  131,   -156,   141,   -171,  179,   -190,  128,   -227,  172,
    -214,  215,   -189,   265,   -244,  322,   -335,  337,   -352,  358,
    -368,  362,   -355,   366,   -381,  403,   -395,  411,   -392,  446,
    -458,  504,   -449,   507,   -464,  452,   -491,  481,   -534,  486,
    -516,  560,   -535,   525,   -537,  559,   -554,  570,   -616,  591,
    -585,  627,   -509,   588,   -584,  547,   -610,  580,   -614,  635,
    -620,  655,   -554,   546,   -591,  642,   -590,  660,   -656,  629,
    -604,  620,   -580,   617,   -645,  648,   -573,  612,   -604,  584,
    -571,  597,   -562,   627,   -550,  560,   -606,  529,   -584,  568,
    -503,  532,   -463,   512,   -440,  399,   -457,  437,   -349,  278,
    -317,  257,   -220,   163,   -8,    -61,   18,    -161,  367,   -1306};
static const int16_t time2spec_out_expected_2[kSamples] = {
    14283, -11552, -15335, 6626,  7554,  -2150, -6309, 1307,  4523,  -4,
    -3908, -314,   3001,   914,   -2715, -1042, 2094,  1272,  -1715, -1399,
    1263,  1508,   -1021,  -1534, 735,   1595,  -439,  -1447, 155,   1433,
    22,    -1325,  -268,   1205,  424,   -1030, -608,  950,   643,   -733,
    -787,  661,    861,    -502,  -888,  331,   852,   -144,  -849,  19,
    833,   99,     -826,   -154,  771,   368,   -735,  -459,  645,   513,
    -491,  -604,   431,    630,   -314,  -598,  183,   622,   -78,   -612,
    -48,   641,    154,    -645,  -257,  610,   281,   -529,  -444,  450,
    441,   -327,   -506,   274,   476,   -232,  -570,  117,   554,   -86,
    -531,  -21,    572,    151,   -606,  -221,  496,   322,   -407,  -388,
    407,   394,    -268,   -428,  280,   505,   -115,  -588,  19,    513,
    -29,   -539,   -109,   468,   173,   -501,  -242,  442,   278,   -478,
    -680,  656,    -659,   656,   -669,  602,   -688,  612,   -667,  612,
    -642,  627,    -648,   653,   -676,  596,   -680,  655,   -649,  678,
    -672,  587,    -608,   637,   -645,  637,   -620,  556,   -580,  553,
    -635,  518,    -599,   583,   -501,  536,   -544,  473,   -552,  583,
    -511,  541,    -532,   563,   -486,  461,   -453,  486,   -388,  424,
    -416,  432,    -374,   399,   -462,  364,   -346,  293,   -329,  331,
    -313,  281,    -247,   309,   -337,  241,   -190,  207,   -194,  179,
    -163,  155,    -156,   117,   -135,  107,   -126,  29,    -22,   81,
    -8,    17,     -61,    -10,   8,     -37,   80,    -44,   72,    -88,
    65,    -89,    130,    -114,  181,   -215,  189,   -245,  260,   -288,
    294,   -339,   344,    -396,  407,   -429,  438,   -439,  485,   -556,
    629,   -612,   637,    -645,  661,   -737,  829,   -830,  831,   -1041};

class TransformTest : public ::testing::Test {
 protected:
  // Pass a function pointer to the Tester function.
  void Time2SpecTester(Time2Spec Time2SpecFunction) {
    // WebRtcIsacfix_Time2Spec functions hard coded the buffer lengths. It's a
    // large buffer but we have to test it here.
    int16_t data_in_1[kSamples] = {0};
    int16_t data_in_2[kSamples] = {0};
    int16_t data_out_1[kSamples] = {0};
    int16_t data_out_2[kSamples] = {0};

    for (int i = 0; i < kSamples; i++) {
      data_in_1[i] = i * i + 1777;
      data_in_2[i] = WEBRTC_SPL_WORD16_MAX / (i + 1) + 17;
    }

    Time2SpecFunction(data_in_1, data_in_2, data_out_1, data_out_2);

    for (int i = 0; i < kSamples; i++) {
      // We don't require bit-exact for ARM assembly code.
      EXPECT_LE(abs(time2spec_out_expected_1[i] - data_out_1[i]), 1);
      EXPECT_LE(abs(time2spec_out_expected_2[i] - data_out_2[i]), 1);
    }
  }

  // Pass a function pointer to the Tester function.
  void Spec2TimeTester(Spec2Time Spec2TimeFunction) {
    // WebRtcIsacfix_Spec2Time functions hard coded the buffer lengths. It's a
    // large buffer but we have to test it here.
    int16_t data_in_1[kSamples] = {0};
    int16_t data_in_2[kSamples] = {0};
    int32_t data_out_1[kSamples] = {0};
    int32_t data_out_2[kSamples] = {0};
    for (int i = 0; i < kSamples; i++) {
      data_in_1[i] = i * i + 1777;
      data_in_2[i] = WEBRTC_SPL_WORD16_MAX / (i + 1) + 17;
    }

    Spec2TimeFunction(data_in_1, data_in_2, data_out_1, data_out_2);

    for (int i = 0; i < kSamples; i++) {
      // We don't require bit-exact for ARM assembly code.
      EXPECT_LE(abs(spec2time_out_expected_1[i] - data_out_1[i]), 16);
      EXPECT_LE(abs(spec2time_out_expected_2[i] - data_out_2[i]), 16);
    }
  }
};

TEST_F(TransformTest, Time2SpecTest) {
  Time2SpecTester(WebRtcIsacfix_Time2SpecC);
#if defined(WEBRTC_HAS_NEON)
  Time2SpecTester(WebRtcIsacfix_Time2SpecNeon);
#endif
}

TEST_F(TransformTest, Spec2TimeTest) {
  Spec2TimeTester(WebRtcIsacfix_Spec2TimeC);
#if defined(WEBRTC_HAS_NEON)
  Spec2TimeTester(WebRtcIsacfix_Spec2TimeNeon);
#endif
}
