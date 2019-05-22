#ifndef __DefMedia_H__
#define __DefMedia_H__

namespace MRPS
{
	enum Audio_Codec
	{
		Audio_Codec_Unknown = 0,
		Audio_Codec_G711A = 200,
		Audio_Codec_G711U,
		Audio_Codec_AMR_NB,		
		Audio_Codec_NVOC,
		Audio_Codec_NVOC_PDT,
		Audio_Codec_AMBE,
		Audio_Codec_TETRA,
		Audio_Codec_AMR_WB,
	};

	enum Audio_Bitrate
	{
		Audio_Bitrate_Unknown = 0,
		Audio_Bitrate_4_75,                       //4.75Kbps
		Audio_Bitrate_12_2,                       //12.2Kbps
	};

	enum Audio_PayloadFormat
	{
		Audio_PayloadFormat_Unknown = 0,
		Audio_PayloadFormat_ByteAlign,
		Audio_PayloadFormat_SaveBandwidth,
	};

	enum Audio_PTime
	{
		Audio_PTime_Unknown = 0,
		Audio_PTime_20,                          //20ms
		Audio_PTime_40,                          //40ms
		Audio_PTime_60,                          //60ms
		Audio_PTime_80,                          //80ms
	};

	enum Audio_PayloadType
	{
		Audio_PayloadType_Unknown = 0,
	};

	enum Video_Codec
	{
		Video_Codec_Unknown = 0,
		Video_Codec_H264,
		Video_Codec_vp8,
		Video_Codec_mpeg4,
		Video_Codec_h263,
	};

	enum Video_Framerate
	{
		Video_Framerate_Unknown = 0,
		Video_Framerate_15,
		Video_Framerate_20,
		Video_Framerate_25,
		Video_Framerate_30,
	};

	enum Video_Framesize
	{
		Video_Framesize_Unknown = 0,
		Video_Framesize_1920_1080,
		Video_Framesize_1280_720,
		Video_Framesize_1024_768,
		Video_Framesize_800_600,
		Video_Framesize_720_576,
		Video_Framesize_704_576,
		Video_Framesize_640_480,
		Video_Framesize_352_288,
		Video_Framesize_320_240,
		Video_Framesize_176_144,
	};

	enum Video_PayloadType
	{
		Video_PayloadType_Unknown = 0,

	};
}

#endif