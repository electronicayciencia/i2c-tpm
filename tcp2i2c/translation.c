const char * tpmtag_to_text(int tag) {
	switch (tag) {
		case 0x00C1: return "TPM_TAG_RQU_COMMAND";
		case 0x00C2: return "TPM_TAG_RQU_AUTH1_COMMAND";
		case 0x00C3: return "TPM_TAG_RQU_AUTH2_COMMAND";
		case 0x00C4: return "TPM_TAG_RSP_COMMAND";
		case 0x00C5: return "TPM_TAG_RSP_AUTH1_COMMAND";
		case 0x00C6: return "TPM_TAG_RSP_AUTH2_COMMAND";
		default: return "Unknown!";
	}
}


const char * ord_to_text(int ord) {
	switch (ord) {
		case 0x0000000A: return "TPM_ORD_OIAP";
		case 0x0000000B: return "TPM_ORD_OSAP";
		case 0x0000000C: return "TPM_ORD_ChangeAuth";
		case 0x0000000D: return "TPM_ORD_TakeOwnership";
		case 0x0000000E: return "TPM_ORD_ChangeAuthAsymStart";
		case 0x0000000F: return "TPM_ORD_ChangeAuthAsymFinish";
		case 0x00000010: return "TPM_ORD_ChangeAuthOwner";
		case 0x00000011: return "TPM_ORD_DSAP";
		case 0x00000012: return "TPM_ORD_CMK_CreateTicket";
		case 0x00000013: return "TPM_ORD_CMK_CreateKey";
		case 0x00000014: return "TPM_ORD_Extend";
		case 0x00000015: return "TPM_ORD_PcrRead";
		case 0x00000016: return "TPM_ORD_Quote";
		case 0x00000017: return "TPM_ORD_Seal";
		case 0x00000018: return "TPM_ORD_Unseal";
		case 0x00000019: return "TPM_ORD_DirWriteAuth";
		case 0x0000001A: return "TPM_ORD_DirRead";
		case 0x0000001B: return "TPM_ORD_CMK_CreateBlob";
		case 0x0000001C: return "TPM_ORD_CMK_SetRestrictions";
		case 0x0000001D: return "TPM_ORD_CMK_ApproveMA";
		case 0x0000001E: return "TPM_ORD_UnBind";
		case 0x0000001F: return "TPM_ORD_CreateWrapKey";
		case 0x00000020: return "TPM_ORD_LoadKey";
		case 0x00000021: return "TPM_ORD_GetPubKey";
		case 0x00000022: return "TPM_ORD_EvictKey";
		case 0x00000023: return "TPM_ORD_KeyControlOwner";
		case 0x00000024: return "TPM_ORD_CMK_ConvertMigration";
		case 0x00000025: return "TPM_ORD_MigrateKey";
		case 0x00000028: return "TPM_ORD_CreateMigrationBlob";
		case 0x00000029: return "TPM_ORD_DAA_Join";
		case 0x0000002A: return "TPM_ORD_ConvertMigrationBlob";
		case 0x0000002B: return "TPM_ORD_AuthorizeMigrationKey";
		case 0x0000002C: return "TPM_ORD_CreateMaintenanceArchive";
		case 0x0000002D: return "TPM_ORD_LoadMaintenanceArchive";
		case 0x0000002E: return "TPM_ORD_KillMaintenanceFeature";
		case 0x0000002F: return "TPM_ORD_LoadManuMaintPub";
		case 0x00000030: return "TPM_ORD_ReadManuMaintPub";
		case 0x00000031: return "TPM_ORD_DAA_Sign";
		case 0x00000032: return "TPM_ORD_CertifyKey";
		case 0x00000033: return "TPM_ORD_CertifyKey2";
		case 0x0000003C: return "TPM_ORD_Sign";
		case 0x0000003D: return "TPM_ORD_Sealx";
		case 0x0000003E: return "TPM_ORD_Quote2";
		case 0x0000003F: return "TPM_ORD_SetCapability";
		case 0x00000040: return "TPM_ORD_ResetLockValue";
		case 0x00000041: return "TPM_ORD_LoadKey2";
		case 0x00000046: return "TPM_ORD_GetRandom";
		case 0x00000047: return "TPM_ORD_StirRandom";
		case 0x00000050: return "TPM_ORD_SelfTestFull";
		case 0x00000052: return "TPM_ORD_CertifySelfTest";
		case 0x00000053: return "TPM_ORD_ContinueSelfTest";
		case 0x00000054: return "TPM_ORD_GetTestResult";
		case 0x0000005A: return "TPM_ORD_Reset";
		case 0x0000005B: return "TPM_ORD_OwnerClear";
		case 0x0000005C: return "TPM_ORD_DisableOwnerClear";
		case 0x0000005D: return "TPM_ORD_ForceClear";
		case 0x0000005E: return "TPM_ORD_DisableForceClear";
		case 0x00000064: return "TPM_ORD_GetCapabilitySigned";
		case 0x00000065: return "TPM_ORD_GetCapability";
		case 0x00000066: return "TPM_ORD_GetCapabilityOwner";
		case 0x0000006E: return "TPM_ORD_OwnerSetDisable";
		case 0x0000006F: return "TPM_ORD_PhysicalEnable";
		case 0x00000070: return "TPM_ORD_PhysicalDisable";
		case 0x00000071: return "TPM_ORD_SetOwnerInstall";
		case 0x00000072: return "TPM_ORD_PhysicalSetDeactivated";
		case 0x00000073: return "TPM_ORD_SetTempDeactivated";
		case 0x00000074: return "TPM_ORD_SetOperatorAuth";
		case 0x00000075: return "TPM_ORD_SetOwnerPointer";
		case 0x00000078: return "TPM_ORD_CreateEndorsementKeyPair";
		case 0x00000079: return "TPM_ORD_MakeIdentity";
		case 0x0000007A: return "TPM_ORD_ActivateIdentity";
		case 0x0000007C: return "TPM_ORD_ReadPubek";
		case 0x0000007D: return "TPM_ORD_OwnerReadPubek";
		case 0x0000007E: return "TPM_ORD_DisablePubekRead";
		case 0x0000007F: return "TPM_ORD_CreateRevocableEK";
		case 0x00000080: return "TPM_ORD_RevokeTrust";
		case 0x00000081: return "TPM_ORD_OwnerReadInternalPub";
		case 0x00000082: return "TPM_ORD_GetAuditEvent";
		case 0x00000083: return "TPM_ORD_GetAuditEventSigned";
		case 0x00000085: return "TPM_ORD_GetAuditDigest";
		case 0x00000086: return "TPM_ORD_GetAuditDigestSigned";
		case 0x0000008C: return "TPM_ORD_GetOrdinalAuditStatus";
		case 0x0000008D: return "TPM_ORD_SetOrdinalAuditStatus";
		case 0x00000096: return "TPM_ORD_Terminate_Handle";
		case 0x00000097: return "TPM_ORD_Init";
		case 0x00000098: return "TPM_ORD_SaveState";
		case 0x00000099: return "TPM_ORD_Startup";
		case 0x0000009A: return "TPM_ORD_SetRedirection";
		case 0x000000A0: return "TPM_ORD_SHA1Start";
		case 0x000000A1: return "TPM_ORD_SHA1Update";
		case 0x000000A2: return "TPM_ORD_SHA1Complete";
		case 0x000000A3: return "TPM_ORD_SHA1CompleteExtend";
		case 0x000000AA: return "TPM_ORD_FieldUpgrade";
		case 0x000000B4: return "TPM_ORD_SaveKeyContext";
		case 0x000000B5: return "TPM_ORD_LoadKeyContext";
		case 0x000000B6: return "TPM_ORD_SaveAuthContext";
		case 0x000000B7: return "TPM_ORD_LoadAuthContext";
		case 0x000000B8: return "TPM_ORD_SaveContext";
		case 0x000000B9: return "TPM_ORD_LoadContext";
		case 0x000000BA: return "TPM_ORD_FlushSpecific";
		case 0x000000C8: return "TPM_ORD_PCR_Reset";
		case 0x000000CC: return "TPM_ORD_NV_DefineSpace";
		case 0x000000CD: return "TPM_ORD_NV_WriteValue";
		case 0x000000CE: return "TPM_ORD_NV_WriteValueAuth";
		case 0x000000CF: return "TPM_ORD_NV_ReadValue";
		case 0x000000D0: return "TPM_ORD_NV_ReadValueAuth";
		case 0x000000D1: return "TPM_ORD_Delegate_UpdateVerification";
		case 0x000000D2: return "TPM_ORD_Delegate_Manage";
		case 0x000000D4: return "TPM_ORD_Delegate_CreateKeyDelegation";
		case 0x000000D5: return "TPM_ORD_Delegate_CreateOwnerDele";
		case 0x000000D6: return "TPM_ORD_Delegate_VerifyDelegation";
		case 0x000000D8: return "TPM_ORD_Delegate_LoadOwnerDelegation";
		case 0x000000DB: return "TPM_ORD_Delegate_ReadTable";
		case 0x000000DC: return "TPM_ORD_CreateCounter";
		case 0x000000DD: return "TPM_ORD_IncrementCounter";
		case 0x000000DE: return "TPM_ORD_ReadCounter";
		case 0x000000DF: return "TPM_ORD_ReleaseCounter";
		case 0x000000E0: return "TPM_ORD_ReleaseCounterOwner";
		case 0x000000E6: return "TPM_ORD_EstablishTransport";
		case 0x000000E7: return "TPM_ORD_ExecuteTransport";
		case 0x000000E8: return "TPM_ORD_ReleaseTransportSigned";
		case 0x000000F1: return "TPM_ORD_GetTicks";
		case 0x000000F2: return "TPM_ORD_TickStampBlob";
		case 0x4000000A: return "TSC_ORD_PhysicalPresence";
		case 0x4000000B: return "TSC_ORD_ResetEstablishmentBit";
		default: return "Unknown!";
	}
}


const char * structuretag_to_text(int tag) {
	switch (tag) {
		case 0x0001: return "TPM_TAG_CONTEXTBLOB";
		case 0x0002: return "TPM_TAG_CONTEXT_SENSITIVE";
		case 0x0003: return "TPM_TAG_CONTEXTPOINTER";
		case 0x0004: return "TPM_TAG_CONTEXTLIST";
		case 0x0005: return "TPM_TAG_SIGNINFO";
		case 0x0006: return "TPM_TAG_PCR_INFO_LONG";
		case 0x0007: return "TPM_TAG_PERSISTENT_FLAGS";
		case 0x0008: return "TPM_TAG_VOLATILE_FLAGS";
		case 0x0009: return "TPM_TAG_PERSISTENT_DATA";
		case 0x000A: return "TPM_TAG_VOLATILE_DATA";
		case 0x000B: return "TPM_TAG_SV_DATA";
		case 0x000C: return "TPM_TAG_EK_BLOB";
		case 0x000D: return "TPM_TAG_EK_BLOB_AUTH";
		case 0x000E: return "TPM_TAG_COUNTER_VALUE";
		case 0x000F: return "TPM_TAG_TRANSPORT_INTERNAL";
		case 0x0010: return "TPM_TAG_TRANSPORT_LOG_IN";
		case 0x0011: return "TPM_TAG_TRANSPORT_LOG_OUT";
		case 0x0012: return "TPM_TAG_AUDIT_EVENT_IN";
		case 0x0013: return "TPM_TAG_AUDIT_EVENT_OUT";
		case 0x0014: return "TPM_TAG_CURRENT_TICKS";
		case 0x0015: return "TPM_TAG_KEY";
		case 0x0016: return "TPM_TAG_STORED_DATA12";
		case 0x0017: return "TPM_TAG_NV_ATTRIBUTES";
		case 0x0018: return "TPM_TAG_NV_DATA_PUBLIC";
		case 0x0019: return "TPM_TAG_NV_DATA_SENSITIVE";
		case 0x001A: return "TPM_TAG_DELEGATIONS";
		case 0x001B: return "TPM_TAG_DELEGATE_PUBLIC";
		case 0x001C: return "TPM_TAG_DELEGATE_TABLE_ROW";
		case 0x001D: return "TPM_TAG_TRANSPORT_AUTH";
		case 0x001E: return "TPM_TAG_TRANSPORT_PUBLIC";
		case 0x001F: return "TPM_TAG_PERMANENT_FLAGS";
		case 0x0020: return "TPM_TAG_STCLEAR_FLAGS";
		case 0x0021: return "TPM_TAG_STANY_FLAGS";
		case 0x0022: return "TPM_TAG_PERMANENT_DATA";
		case 0x0023: return "TPM_TAG_STCLEAR_DATA";
		case 0x0024: return "TPM_TAG_STANY_DATA";
		case 0x0025: return "TPM_TAG_FAMILY_TABLE_ENTRY";
		case 0x0026: return "TPM_TAG_DELEGATE_SENSITIVE";
		case 0x0027: return "TPM_TAG_DELG_KEY_BLOB";
		case 0x0028: return "TPM_TAG_KEY12";
		case 0x0029: return "TPM_TAG_CERTIFY_INFO2";
		case 0x002A: return "TPM_TAG_DELEGATE_OWNER_BLOB";
		case 0x002B: return "TPM_TAG_EK_BLOB_ACTIVATE";
		case 0x002C: return "TPM_TAG_DAA_BLOB";
		case 0x002D: return "TPM_TAG_DAA_CONTEXT";
		case 0x002E: return "TPM_TAG_DAA_ENFORCE";
		case 0x002F: return "TPM_TAG_DAA_ISSUER";
		case 0x0030: return "TPM_TAG_CAP_VERSION_INFO";
		case 0x0031: return "TPM_TAG_DAA_SENSITIVE";
		case 0x0032: return "TPM_TAG_DAA_TPM";
		case 0x0033: return "TPM_TAG_CMK_MIGAUTH";
		case 0x0034: return "TPM_TAG_CMK_SIGTICKET";
		case 0x0035: return "TPM_TAG_CMK_MA_APPROVAL";
		case 0x0036: return "TPM_TAG_QUOTE_INFO2";
		case 0x0037: return "TPM_TAG_DA_INFO";
		case 0x0038: return "TPM_TAG_DA_INFO_LIMITED";
		case 0x0039: return "TPM_TAG_DA_ACTION_TYPE";
		default: return "Unknown!";
	}
}


const char * returncode_to_text(int code) {
	switch (code) {
		case 0: return "TPM_SUCCESS";
		case 1: return "TPM_AUTHFAIL";
		case 2: return "TPM_BADINDEX";
		case 3: return "TPM_BAD_PARAMETER";
		case 4: return "TPM_AUDITFAILURE";
		case 5: return "TPM_CLEAR_DISABLED";
		case 6: return "TPM_DEACTIVATED";
		case 7: return "TPM_DISABLED";
		case 8: return "TPM_DISABLED_CMD";
		case 9: return "TPM_FAIL";
		case 10: return "TPM_BAD_ORDINAL";
		case 11: return "TPM_INSTALL_DISABLED";
		case 12: return "TPM_INVALID_KEYHANDLE";
		case 13: return "TPM_KEYNOTFOUND";
		case 14: return "TPM_INAPPROPRIATE_ENC";
		case 15: return "TPM_MIGRATEFAIL";
		case 16: return "TPM_INVALID_PCR_INFO";
		case 17: return "TPM_NOSPACE";
		case 18: return "TPM_NOSRK";
		case 19: return "TPM_NOTSEALED_BLOB";
		case 20: return "TPM_OWNER_SET";
		case 21: return "TPM_RESOURCES";
		case 22: return "TPM_SHORTRANDOM";
		case 23: return "TPM_SIZE";
		case 24: return "TPM_WRONGPCRVAL";
		case 25: return "TPM_BAD_PARAM_SIZE";
		case 26: return "TPM_SHA_THREAD";
		case 27: return "TPM_SHA_ERROR";
		case 28: return "TPM_FAILEDSELFTEST";
		case 29: return "TPM_AUTH2FAIL";
		case 30: return "TPM_BADTAG";
		case 31: return "TPM_IOERROR";
		case 32: return "TPM_ENCRYPT_ERROR";
		case 33: return "TPM_DECRYPT_ERROR";
		case 34: return "TPM_INVALID_AUTHHANDLE";
		case 35: return "TPM_NO_ENDORSEMENT";
		case 36: return "TPM_INVALID_KEYUSAGE";
		case 37: return "TPM_WRONG_ENTITYTYPE";
		case 38: return "TPM_INVALID_POSTINIT";
		case 39: return "TPM_INAPPROPRIATE_SIG";
		case 40: return "TPM_BAD_KEY_PROPERTY";
		case 41: return "TPM_BAD_MIGRATION";
		case 42: return "TPM_BAD_SCHEME";
		case 43: return "TPM_BAD_DATASIZE";
		case 44: return "TPM_BAD_MODE";
		case 45: return "TPM_BAD_PRESENCE";
		case 46: return "TPM_BAD_VERSION";
		case 47: return "TPM_NO_WRAP_TRANSPORT";
		case 48: return "TPM_AUDITFAIL_UNSUCCESSFUL";
		case 49: return "TPM_AUDITFAIL_SUCCESSFUL";
		case 50: return "TPM_NOTRESETABLE";
		case 51: return "TPM_NOTLOCAL";
		case 52: return "TPM_BAD_TYPE";
		case 53: return "TPM_INVALID_RESOURCE";
		case 54: return "TPM_NOTFIPS";
		case 55: return "TPM_INVALID_FAMILY";
		case 56: return "TPM_NO_NV_PERMISSION";
		case 57: return "TPM_REQUIRES_SIGN";
		case 58: return "TPM_KEY_NOTSUPPORTED";
		case 59: return "TPM_AUTH_CONFLICT";
		case 60: return "TPM_AREA_LOCKED";
		case 61: return "TPM_BAD_LOCALITY";
		case 62: return "TPM_READ_ONLY";
		case 63: return "TPM_PER_NOWRITE";
		case 64: return "TPM_FAMILYCOUNT";
		case 65: return "TPM_WRITE_LOCKED";
		case 66: return "TPM_BAD_ATTRIBUTES";
		case 67: return "TPM_INVALID_STRUCTURE";
		case 68: return "TPM_KEY_OWNER_CONTROL";
		case 69: return "TPM_BAD_COUNTER";
		case 70: return "TPM_NOT_FULLWRITE";
		case 71: return "TPM_CONTEXT_GAP";
		case 72: return "TPM_MAXNVWRITES";
		case 73: return "TPM_NOOPERATOR";
		case 74: return "TPM_RESOURCEMISSING";
		case 75: return "TPM_DELEGATE_LOCK";
		case 76: return "TPM_DELEGATE_FAMILY";
		case 77: return "TPM_DELEGATE_ADMIN";
		case 78: return "TPM_TRANSPORT_NOTEXCLUSIVE";
		case 79: return "TPM_OWNER_CONTROL";
		case 80: return "TPM_DAA_RESOURCES";
		case 81: return "TPM_DAA_INPUT_DATA0";
		case 82: return "TPM_DAA_INPUT_DATA1";
		case 83: return "TPM_DAA_ISSUER_SETTINGS";
		case 84: return "TPM_DAA_TPM_SETTINGS";
		case 85: return "TPM_DAA_STAGE";
		case 86: return "TPM_DAA_ISSUER_VALIDITY";
		case 87: return "TPM_DAA_WRONG_W";
		case 88: return "TPM_BAD_HANDLE";
		case 89: return "TPM_BAD_DELEGATE";
		case 90: return "TPM_BADCONTEXT";
		case 91: return "TPM_TOOMANYCONTEXTS";
		case 92: return "TPM_MA_TICKET_SIGNATURE";
		case 93: return "TPM_MA_DESTINATION";
		case 94: return "TPM_MA_SOURCE";
		case 95: return "TPM_MA_AUTHORITY";
		case 97: return "TPM_PERMANENTEK";
		case 98: return "TPM_BAD_SIGNATURE";
		case 99: return "TPM_NOCONTEXTSPACE";
		default: return "Unknown!";
	}
}


