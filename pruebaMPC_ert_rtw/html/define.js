function CodeDefine() { 
this.def = new Array();
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:33,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:70,type:"fcn"};
this.def["pruebaMPC_B"] = {file: "pruebaMPC_c.html",line:23,type:"var"};
this.def["pruebaMPC_X"] = {file: "pruebaMPC_c.html",line:26,type:"var"};
this.def["pruebaMPC_DW"] = {file: "pruebaMPC_c.html",line:29,type:"var"};
this.def["pruebaMPC_Y"] = {file: "pruebaMPC_c.html",line:32,type:"var"};
this.def["pruebaMPC_M_"] = {file: "pruebaMPC_c.html",line:35,type:"var"};
this.def["pruebaMPC_M"] = {file: "pruebaMPC_c.html",line:36,type:"var"};
this.def["rate_scheduler"] = {file: "pruebaMPC_c.html",line:54,type:"fcn"};
this.def["rt_ertODEUpdateContinuousStates"] = {file: "pruebaMPC_c.html",line:70,type:"fcn"};
this.def["pruebaMPC_mpcblock_refmd"] = {file: "pruebaMPC_c.html",line:137,type:"fcn"};
this.def["pruebaMPC_mpcblock_optimizer"] = {file: "pruebaMPC_c.html",line:155,type:"fcn"};
this.def["pruebaMPC_step"] = {file: "pruebaMPC_c.html",line:209,type:"fcn"};
this.def["pruebaMPC_derivatives"] = {file: "pruebaMPC_c.html",line:23115,type:"fcn"};
this.def["pruebaMPC_initialize"] = {file: "pruebaMPC_c.html",line:23150,type:"fcn"};
this.def["pruebaMPC_terminate"] = {file: "pruebaMPC_c.html",line:23215,type:"fcn"};
this.def["B_pruebaMPC_T"] = {file: "pruebaMPC_h.html",line:60,type:"type"};
this.def["DW_pruebaMPC_T"] = {file: "pruebaMPC_h.html",line:67,type:"type"};
this.def["X_pruebaMPC_T"] = {file: "pruebaMPC_h.html",line:72,type:"type"};
this.def["XDot_pruebaMPC_T"] = {file: "pruebaMPC_h.html",line:77,type:"type"};
this.def["XDis_pruebaMPC_T"] = {file: "pruebaMPC_h.html",line:82,type:"type"};
this.def["ODE4_IntgData"] = {file: "pruebaMPC_h.html",line:91,type:"type"};
this.def["ConstP_pruebaMPC_T"] = {file: "pruebaMPC_h.html",line:106,type:"type"};
this.def["ExtY_pruebaMPC_T"] = {file: "pruebaMPC_h.html",line:111,type:"type"};
this.def["RT_MODEL_pruebaMPC_T"] = {file: "pruebaMPC_types_h.html",line:20,type:"type"};
this.def["pruebaMPC_ConstP"] = {file: "pruebaMPC_data_c.html",line:20,type:"var"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:47,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:48,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:50,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["creal32_T"] = {file: "rtwtypes_h.html",line:78,type:"type"};
this.def["creal64_T"] = {file: "rtwtypes_h.html",line:83,type:"type"};
this.def["creal_T"] = {file: "rtwtypes_h.html",line:88,type:"type"};
this.def["cint8_T"] = {file: "rtwtypes_h.html",line:95,type:"type"};
this.def["cuint8_T"] = {file: "rtwtypes_h.html",line:102,type:"type"};
this.def["cint16_T"] = {file: "rtwtypes_h.html",line:109,type:"type"};
this.def["cuint16_T"] = {file: "rtwtypes_h.html",line:116,type:"type"};
this.def["cint32_T"] = {file: "rtwtypes_h.html",line:123,type:"type"};
this.def["cuint32_T"] = {file: "rtwtypes_h.html",line:130,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:148,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["pruebaMPC_c.html"] = "../pruebaMPC.c";
	this.html2Root["pruebaMPC_c.html"] = "pruebaMPC_c.html";
	this.html2SrcPath["pruebaMPC_h.html"] = "../pruebaMPC.h";
	this.html2Root["pruebaMPC_h.html"] = "pruebaMPC_h.html";
	this.html2SrcPath["pruebaMPC_private_h.html"] = "../pruebaMPC_private.h";
	this.html2Root["pruebaMPC_private_h.html"] = "pruebaMPC_private_h.html";
	this.html2SrcPath["pruebaMPC_types_h.html"] = "../pruebaMPC_types.h";
	this.html2Root["pruebaMPC_types_h.html"] = "pruebaMPC_types_h.html";
	this.html2SrcPath["pruebaMPC_data_c.html"] = "../pruebaMPC_data.c";
	this.html2Root["pruebaMPC_data_c.html"] = "pruebaMPC_data_c.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","pruebaMPC_c.html","pruebaMPC_h.html","pruebaMPC_private_h.html","pruebaMPC_types_h.html","pruebaMPC_data_c.html","rtwtypes_h.html"];
