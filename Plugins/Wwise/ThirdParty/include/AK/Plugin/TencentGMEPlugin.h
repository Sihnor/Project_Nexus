/** Copyright (c) 2018-2028 Tencent Technology All Right Reserved.
* @file       TencentGMEPlugin.h
* @brief      Game Multimedia Engine(GME) Plugin
* @version    2019-01-07 gaopenggao create this file
*******************************************************************************/

// TencentGMEPlugin.h

#ifndef _TENCENTGMEPLUGIN_API_H_
#define _TENCENTGMEPLUGIN_API_H_

#if defined (__APPLE__) || defined(ANDROID) || defined(__linux__) || defined(AK_PS4) || defined(AK_PS5) || defined(AK_NX)
#define GMEPlugin_API_CALL
#elif defined(_WIN32)
#define GMEPlugin_API_CALL __cdecl
#endif

enum GMEWWisePlugin_TeamMode
{
	TEAMMODE_GLOBAL = 0,
	TEAMMODE_TEAM = 1
};

enum GMEWWisePlugin_Region
{
	REGION_DEFAULT = 0,
	REGION_INTERNATIONAL = 1,
	REGION_AWS = 2,
};

enum GMEWWisePlugin_STREAMPROIFLE
{
	STREAMPROFILE_LOW_LATENCY = 1,
	STREAMPROFILE_STANDARD = 2,
	STREAMPROFILE_HD = 3
};

enum GMEWWisePlugin_LogLevel
{
	GMESDK_LOGLEVEL_NONE = 0,
	GMESDK_LOGLEVEL_ERROR = 1,
	GMESDK_LOGLEVEL_INFO = 2,
	GMESDK_LOGLEVEL_DEBUG = 3,
	GMESDK_LOGLEVEL_VERBOSE = 4
};

/**
* @brief Get version information of GME plugin lib
* @return GME plugin version.
*/
extern "C"
const char* GMEWWisePlugin_GetVersion();

/**
* @brief Set the local user ID for the local user. Each GME user must have a unique identifier.
*	This function must be called before posting events sending or receiving to 
*	GME servers.
* @param[in] userID The identifier of the local GME user.
*	The value is a 64-bit integer data and should be greater than 10000. It needs to be
*	converted into character type.
* @return Code to indicate if UserID is a valid value.
*	0: UserID is set successfully.
*	-1: NULL or empty string, -2: non-digit character, -3: not greater than 10000
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_SetUserID(const char* userID);

/**
* @brief Set the GME chat room ID.
*	This function must be called before posting events sending or receiving to 
*	GME servers.
*	Setting a new roomID will not affect already playing voices.
* @param[in] roomID Alphanumeric character string of up to 127 characters identifying a 
*	GME chatting room.
* @return Code to indicate if UserID is a valid value.
*	0: RoomID is set successfully.
*	-1: NULL or empty string
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_SetRoomID(const char* roomID);

/**
* @brief Set the mapping between a Wwise game object ID and a GME user ID
*	corresponding to a user. A mapping between gameObjectID and userID is used
*	by GME to decide whether a GME Receive plug-in instance should play a
*	specific userID or, if there is no mapping, the mix of all voice streams within
*	the currently set roomID.
* @param[in] gameObjectID The gameObjectID allocated in the game.
* @param[in] userID The user ID of the GME user. Passing NULL or "" (empty string)
*	clears a previously set mapping.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_ReceivePlugin_SetReceiveOpenIDWithGameObjectID(AkUInt64 gameObjectID, const char* userID);

/**
* @brief Get the mapping between a Wwise game object ID and a GME user ID
*	corresponding to a user.
* @param[in] gameObjectID The gameObjectID allocated in the game.
* @param[out] userID User-allocated character buffer of maximum size specified by maxlen.
*	The userID mapped to the gameObjectID will be copied to the buffer if one exists.
* @param[in] maxlen The maximum size of the character buffer userID.
*/
extern "C" 
void GMEPlugin_API_CALL GMEWWisePlugin_ReceivePlugin_GetReceiveOpenIDWithGameObjectID(AkUInt64 gameObjectID, char* userID, int maxlen = 128);

/**
* @brief Enable or disable audio loopback. Loopback controls if sound related to the
*	specified game object is routed back to Wwise to be played on the local device.
*	The audio is always sent to the server, but will only be played locally if loopback
*	is enabled.
* @param[in] gameObjectID The gameObjectID allocated in the game.
* @param[in] enableLoopback Loopback flag value.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SendPlugin_EnableLoopbackWithGameObjectID(AkUInt64 gameObjectID, bool enableLoopback);

/**
* @brief Get the loopback status. Retrieve whether loopback is enabled or disabled for
*	a given game object. Loopback controls if sound posted on the specified game
*	object is routed back to Wwise to be played on the local device.
*	The audio is always sent to the server, but will only be played locally if loopback
*	is enabled.
* @param[in] gameObjectID The gameObjectID allocated in the game.
* @return The loopback status.
*/
extern "C"
bool GMEPlugin_API_CALL GMEWWisePlugin_SendPlugin_GetEnableLoopbackWithGameObjectID(AkUInt64 gameObjectID);

/**
* @brief Set the GME connection region.
* @param[in] region name of GME connection region.
*      REGION_DEFAULT: default settings
*      REGION_INTERNATIONAL: data is stored in Singapore
*      REGION_AWS: AWS infrastructure(TBD)
*/

extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SetRegion(GMEWWisePlugin_Region region);

/**
* @brief Set audio profile of the chat room
* @param[in] profile The room type profile index
*      STREAMPROFILE_LOW_LATENCY: Smooth sound quality and ultra-low delay, 
*			which is suitable for group chat in games like FPS and MOBA games.
*      STREAMPROFILE_STANDARD: Good sound quality and acceptable delay, 
*			which is suitable for voice chat scenarios in casual games like Werewolf and board games.
*      STREAMPROFILE_HD: HD sound quality and relative high delay, 
*			which is suitable for scenarios demanding high sound quality such as music playback and online karaoke.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SetAudioStreamProfile(GMEWWisePlugin_STREAMPROIFLE profile);

/**
* @brief Set the level of logging for the GME SDK library.
*	For log files, default values are GMESDK_LOGLEVEL_INFO in debug builds and
*	GMESDK_LOGLEVEL_ERROR in release builds.
*	For console print, default values are GMESDK_LOGLEVEL_INFO in debug builds and
*	GMESDK_LOGLEVEL_NONE in release builds.
* @param[in] levelWrite Logging level for saved log file.
* @param[in] levelPrint Logging level for console printing.
* @sa GMEWWisePlugin_LogLevel
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SetLogLevel(GMEWWisePlugin_LogLevel levelWrite, GMEWWisePlugin_LogLevel levelPrint);

/**
* @brief Suspend GME related activities.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_Pause();

/**
* @brief Resume GME related activities.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_Resume();

/**
* @brief Get real-time level of the sending voice stream.
* @return Normalized level values from 0 to 100.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_GetAudioSendStreamLevel();

/**
* @brief Get real-time level of a receiving voice stream specified by the targetID.
* @param[in] targetID The identifier of the GME user.
* @return Normalized level values from 0 to 100.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_GetAudioRecvStreamLevel(const char* targetID);

/**
* @brief Add a member specified by the targetID into the blocklist,
*	so as to mute the voice from this member.
* @param[in] targetID The identifier of the GME user.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_AddAudioBlockList(const char* targetID);

/**
* @brief Remove a member specified by the targetID from the blocklist,
*	so as to unmute the voice from this member.
* @param[in] targetID The identifier of the GME user.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_RemoveAudioBlockList(const char* targetID);

/**
* @brief When Bluetooth headset is connected, use headset mic or use device mic,
*	this API is only for the mobile device.
* @param[in] enable Ture means use headset mic, false means use device mic.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_EnableBluetoothMic(bool enable);

/*
	The following APIs are only for the proximity voice. For normal voice chat use cases,
	these APIs don't need to be called.
*/

/**
* @brief Set the team ID for the current player.
*	Players with the same team ID can always talk to each other,
*	regardless of the distance between them in any team mode.
*	A team is a group of players sharing the same team ID within the same room.
* @param[in] teamID Integer value identifying a team ID.
*	A team ID of 0 indicates "No team", and will deactivate any filtering done on the
*	server when routing voices to this user.
* @sa GMEWWisePlugin_SetRangeAudioTeamMode
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SetRangeAudioTeamID(int teamID);

/**
* @brief Set the team mode to use for the current player.
* @param[in] teamMode The communication mode for the current player
*	* TEAMMODE_GLOBAL: Sound from players of any team is received if their position 
*		is within the receiving range.
*		Sound from players in the same team is always received.
*	* TEAMMODE_TEAM: Sound is only received from teammates, i.e., players sharing 
*		the same team ID as the current player.
*		Filtering based on the distance range is not applied.
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SetRangeAudioTeamMode(GMEWWisePlugin_TeamMode teamMode);

/**
* @brief Set the hearing distance between players in global team mode.
*	In global team mode, sound from players with a different team ID 
*	will be received when their position is within range.
*	The range is the 3D distance between player positions, as set by 
*	GMEWWisePlugin_SetSelfPosition.
*	The filtering applied by this range is done on the server.
* @param[in] range Integer value represents the hearing distance.
* @sa GMEWWisePlugin_SetSelfPosition
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SetRangeAudioRecvRange(int range);

/**
* @brief Set the position of the current player.
* @param[in] positionX The X-coordinate of the current player
* @param[in] positionY The Y-coordinate of the current player
* @param[in] positionZ The Z-coordinate of the current player
* @sa GMEWWisePlugin_SetRangeAudioRecvRange
*/
extern "C"
void GMEPlugin_API_CALL GMEWWisePlugin_SetSelfPosition(int positionX, int positionY, int positionZ);

/*
	The following APIs are for the voice message and speech to text.
*/

/**
* @brief Start recording speech, which will be recognized and uploaded to the server.
*	The maximum duration of speech is 60 seconds. Recording will be stopped 
*	automatically if GMEWWisePlugin_StopRecording() is not called.
*	After calling GMEWWisePlugin_StopRecording(), periodically call
*	GMEWWisePlugin_GetMessage() to obtain the fileID of the recorded speech, 
*	together with the speech recognition result in UTF-8 format.
*	The event type will be GMESDK_MESSAGETYPE_RECORD_COMPLETE.
* @param[in] speechLanguage Language tag for the speech.
*	Refer to the user manual for the language tags supported.
*	If the language tag is set to an empty string, only uploading will be done.
*	See https://intl.cloud.tencent.com/document/product/607/30260 for an 
*	up-to-date list of supported languages.
* @return Return code:
*	0: Success.
*	Other values: Ref to Errorcode section in the user manual.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_StartRecording(const char* speechLanguage);

/**
* @brief Stop recording speech. 
* @return Return code:
*	0: Success.
*	Other values: Ref to PTT Errorcode section in the user manual.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_StopRecording();

/**
* @brief Download and play the recording specified by fileID, which is stored on the server.
*	Periodically call GMEWWisePlugin_GetMessage() to obtain the result as a
*	GMESDK_MESSAGETYPE_PLAYOUT_COMPLETE event.
* @param[in] fileid fileID of the recording to be downloaded and played.
* @return Return code:
*	0: Success.
*	Other values: Ref to PTT Errorcode section in the user manual.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_PlayRecordFile(const char *fileid);

/**
* @brief Stop playing speech.
* @return Return code:
*	0: Success.
*	Other values: Ref to PTT Errorcode section in the user manual.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_StopPlayFile();

/**
* @brief Recognize the speech specified by the fileID.
*	Periodically call GMEWWisePlugin_GetMessage() to obtain the result as a
*	GMESDK_MESSAGETYPE_ASR_COMPLETE event.
*	The result will be in UTF-8 format.
* @param[in] fileid fileID of the speech to be recognized.
* @param[in] speechLanguage Language tag for the speech.
*	Ref to the user manual all for the language tags supported.
* @param[in] translateLanguage Not supported now, pass empty string.
* @return Return code:
*	0: Success.
*	Other values: Ref to PTT Errorcode section in the user manual.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_SpeechToText(const char *fileid, const char* speechLanguage, const char* translateLanguage);

/**
* @brief Get speech duration specified by the fileID.
*	Periodically call GMEWWisePlugin_GetMessage() to obtain the result as a
*	GMESDK_MESSAGETYPE_GETVOICEDURATION_COMPLETE event.
* @param[in] fileid fileID of the speech.
* @return Return code:
*	0: Success.
*	Other values: Ref to PTT Errorcode section in the user manual.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_GetVoiceFileDuration(const char* fileid);

/*
	The following API is used to get notification from GME for different message type
*/

/**
* @brief Get GME specific messages.
* @param[out] localUTCTime Unix time of the message.
* @param[out] messageType Message type, ref to the following detailed description.
* @param[out] code Message code according to the message type, ref to the 
*	following detailed description.
* @param[out] message1 Content of Message1
* @param[in] len1 Length of the message1 array.
* @param[out] message2 Content of Message2
* @param[in] len2 Length of the message2 array.
* @return Flag to indicate if there are any new messages. 
*	0: There are new messages to be received.
*	1: No messages to be received.
*/
extern "C"
int GMEPlugin_API_CALL GMEWWisePlugin_GetMessage(int* localUTCTime, int* messageType, int* code, char* message1, int len1, char* message2, int len2);

/*
	For the GMEWWisePlugin_GetMessage() API, the message types and corresponding message codes are listed below. 
	New types and codes maybe added in future development according to the development. 
*/

/* Message type: Errors which may lead to the failure of GME voice communication.
* Possible error codes for this message type:
*	GMESDK_Code_Error_ServerKickYouOut: be kicked out of the chat room. eg. service capacity problem.
*	GMESDK_Code_Error_ServerRequestError: Cannot connect to GME's network.
*	GMESDK_Code_Error_ServerConnectionError: Cannot connect to the interface machine.
*	GMESDK_Code_Error_ServerConnectionTimeOut: Network is unavailable, GME will try to reconnect.
*	GMESDK_Code_Error_ServerConnectionBreak: GME connection is lost, GME will try to reconnect.
*	GMESDK_Code_Error_ChargeOverdue: Charge is overdue. GME service is stopped.
*	GMESDK_Code_Error_ServiceNotOpen: GME service is not enabled from the console.
*	GMESDK_Code_Error_AuthenticationFailed: authentication error.
*	GMESDK_Code_Error_RoomidIncorrect: RoomID cannot be set to empty string.
*	GMESDK_Code_Error_UseridIncorrect: UserID cannot be set to empty string.
*/
#define GMESDK_MESSAGETYPE_ERROR 1

/**
* Message type: Chat Room status
* Possible codes for this message type:
*	GMESDK_Code_RoomStatus_Entering: Connecting
*	GMESDK_Code_RoomStatus_Entered Connected
*	GMESDK_Code_RoomStatus_Exiting Disconnecting
*	GMESDK_Code_RoomStatus_Exited Disconnected
*/
#define GMESDK_MESSAGETYPE_ROOMSTATUS 101

#define GMESDK_Code_RoomStatus_Entering 1
#define GMESDK_Code_RoomStatus_Entered 2
#define GMESDK_Code_RoomStatus_Exiting 3
#define GMESDK_Code_RoomStatus_Exited 0

/**
* Message type: a member has joined the chat room
*	the message argument specifies the member ID in string format.
*	Each member corresponds a separate message.
* code is always zero
*/
#define GMESDK_MESSAGETYPE_ROOMMEMBERIN  102

/**
* Message type: a member has left the chat room
*	the message argument specifies the member ID in string format.
*	Each member corresponds a separate message.
* code is always zero
*/
#define GMESDK_MESSAGETYPE_ROOMMEMBEROUT 103

/**
* Message type: Speech Record and Upload 
* code = 0 Success
* code != 0 Ref to PTT Errorcode section in this file
*/
#define GMESDK_MESSAGETYPE_RECORD_COMPLETE 104

/**
* Message type: Speech Download and Playback
* code = 0 Success
* code != 0 Ref to PTT Errorcode section in this file
*/
#define GMESDK_MESSAGETYPE_PLAYOUT_COMPLETE 105

/**
* Message type: Speech Recognization
* code = 0 Success
* code != 0 Ref to PTT Errorcode section in this file
*/
#define GMESDK_MESSAGETYPE_ASR_COMPLETE 106

/**
* Message type: Speech Duration
* code = 0 Success
* code != 0 Ref to PTT Errorcode section in this file
*/
#define GMESDK_MESSAGETYPE_GETVOICEDURATION_COMPLETE 107

/**
* PTT Errorcode
* Possible error codes for voice message and speech to text:
*	GMESDK_Code_Error_ChargeOverdue: Charge is overdue. GME service is stopped.
*	GMESDK_Code_Error_ServiceNotOpen: GME service is not enabled from the console.
*	GMESDK_Code_Error_AuthenticationFailed: authentication error.
*	GMESDK_Code_Error_ServerRequestFailed: GME backend request issue.
*	GMESDK_Code_Error_NetWorkFailed: Network issue.
*	GMESDK_Code_Error_COSInvalid: FileID is empty, incorrect or invalid.
*	GMESDK_Code_Error_RecordShort: Recording is less than 1s.
*	GMESDK_Code_Error_UnknownError: GME team specific error codes.
*/

/*
* GME Error Codes definition
*/
#define GMESDK_Code_Error_ServerKickYouOut 10003
#define GMESDK_Code_Error_ServerRequestError 10004
#define GMESDK_Code_Error_ServerConnectionError 10005
#define GMESDK_Code_Error_ServerConnectionBreak 10006
#define GMESDK_Code_Error_ServerConnectionTimeOut 10007
#define GMESDK_Code_Error_ChargeOverdue 10011
#define GMESDK_Code_Error_ServiceNotOpen 10012
#define GMESDK_Code_Error_AuthenticationFailed 10013
#define GMESDK_Code_Error_RoomidIncorrect 10014
#define GMESDK_Code_Error_UseridIncorrect 10015
#define GMESDK_Code_Error_ServerRequestFailed 10020
#define GMESDK_Code_Error_NetWorkFailed 10021
#define GMESDK_Code_Error_COSInvalid 10022
#define GMESDK_Code_Error_RecordShort 10023
#define GMESDK_Code_Error_UnknownError 65536

#endif // _TENCENTGMEPLUGIN_API_H_
