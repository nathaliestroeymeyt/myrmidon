// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.24.0-devel
// 	protoc        v3.6.1
// source: TagFamily.proto

package fort_myrmidon_pb

import (
	proto "github.com/golang/protobuf/proto"
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

// This is a compile-time assertion that a sufficiently up-to-date version
// of the legacy proto package is being used.
const _ = proto.ProtoPackageIsVersion4

type TagFamily int32

const (
	TagFamily_UNSET         TagFamily = 0
	TagFamily_TAG16H5       TagFamily = 1
	TagFamily_TAG25H9       TagFamily = 2
	TagFamily_TAG36ARTAG    TagFamily = 3
	TagFamily_TAG36H10      TagFamily = 4
	TagFamily_TAG36H11      TagFamily = 5
	TagFamily_CIRCLE21H7    TagFamily = 6
	TagFamily_CIRCLE49H12   TagFamily = 7
	TagFamily_CUSTOM48H12   TagFamily = 8
	TagFamily_STANDARD41H12 TagFamily = 9
	TagFamily_STANDARD52H13 TagFamily = 10
)

// Enum value maps for TagFamily.
var (
	TagFamily_name = map[int32]string{
		0:  "UNSET",
		1:  "TAG16H5",
		2:  "TAG25H9",
		3:  "TAG36ARTAG",
		4:  "TAG36H10",
		5:  "TAG36H11",
		6:  "CIRCLE21H7",
		7:  "CIRCLE49H12",
		8:  "CUSTOM48H12",
		9:  "STANDARD41H12",
		10: "STANDARD52H13",
	}
	TagFamily_value = map[string]int32{
		"UNSET":         0,
		"TAG16H5":       1,
		"TAG25H9":       2,
		"TAG36ARTAG":    3,
		"TAG36H10":      4,
		"TAG36H11":      5,
		"CIRCLE21H7":    6,
		"CIRCLE49H12":   7,
		"CUSTOM48H12":   8,
		"STANDARD41H12": 9,
		"STANDARD52H13": 10,
	}
)

func (x TagFamily) Enum() *TagFamily {
	p := new(TagFamily)
	*p = x
	return p
}

func (x TagFamily) String() string {
	return protoimpl.X.EnumStringOf(x.Descriptor(), protoreflect.EnumNumber(x))
}

func (TagFamily) Descriptor() protoreflect.EnumDescriptor {
	return file_TagFamily_proto_enumTypes[0].Descriptor()
}

func (TagFamily) Type() protoreflect.EnumType {
	return &file_TagFamily_proto_enumTypes[0]
}

func (x TagFamily) Number() protoreflect.EnumNumber {
	return protoreflect.EnumNumber(x)
}

// Deprecated: Use TagFamily.Descriptor instead.
func (TagFamily) EnumDescriptor() ([]byte, []int) {
	return file_TagFamily_proto_rawDescGZIP(), []int{0}
}

var File_TagFamily_proto protoreflect.FileDescriptor

var file_TagFamily_proto_rawDesc = []byte{
	0x0a, 0x0f, 0x54, 0x61, 0x67, 0x46, 0x61, 0x6d, 0x69, 0x6c, 0x79, 0x2e, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x12, 0x10, 0x66, 0x6f, 0x72, 0x74, 0x2e, 0x6d, 0x79, 0x72, 0x6d, 0x69, 0x64, 0x6f, 0x6e,
	0x2e, 0x70, 0x62, 0x2a, 0xb4, 0x01, 0x0a, 0x09, 0x54, 0x61, 0x67, 0x46, 0x61, 0x6d, 0x69, 0x6c,
	0x79, 0x12, 0x09, 0x0a, 0x05, 0x55, 0x4e, 0x53, 0x45, 0x54, 0x10, 0x00, 0x12, 0x0b, 0x0a, 0x07,
	0x54, 0x41, 0x47, 0x31, 0x36, 0x48, 0x35, 0x10, 0x01, 0x12, 0x0b, 0x0a, 0x07, 0x54, 0x41, 0x47,
	0x32, 0x35, 0x48, 0x39, 0x10, 0x02, 0x12, 0x0e, 0x0a, 0x0a, 0x54, 0x41, 0x47, 0x33, 0x36, 0x41,
	0x52, 0x54, 0x41, 0x47, 0x10, 0x03, 0x12, 0x0c, 0x0a, 0x08, 0x54, 0x41, 0x47, 0x33, 0x36, 0x48,
	0x31, 0x30, 0x10, 0x04, 0x12, 0x0c, 0x0a, 0x08, 0x54, 0x41, 0x47, 0x33, 0x36, 0x48, 0x31, 0x31,
	0x10, 0x05, 0x12, 0x0e, 0x0a, 0x0a, 0x43, 0x49, 0x52, 0x43, 0x4c, 0x45, 0x32, 0x31, 0x48, 0x37,
	0x10, 0x06, 0x12, 0x0f, 0x0a, 0x0b, 0x43, 0x49, 0x52, 0x43, 0x4c, 0x45, 0x34, 0x39, 0x48, 0x31,
	0x32, 0x10, 0x07, 0x12, 0x0f, 0x0a, 0x0b, 0x43, 0x55, 0x53, 0x54, 0x4f, 0x4d, 0x34, 0x38, 0x48,
	0x31, 0x32, 0x10, 0x08, 0x12, 0x11, 0x0a, 0x0d, 0x53, 0x54, 0x41, 0x4e, 0x44, 0x41, 0x52, 0x44,
	0x34, 0x31, 0x48, 0x31, 0x32, 0x10, 0x09, 0x12, 0x11, 0x0a, 0x0d, 0x53, 0x54, 0x41, 0x4e, 0x44,
	0x41, 0x52, 0x44, 0x35, 0x32, 0x48, 0x31, 0x33, 0x10, 0x0a, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x33,
}

var (
	file_TagFamily_proto_rawDescOnce sync.Once
	file_TagFamily_proto_rawDescData = file_TagFamily_proto_rawDesc
)

func file_TagFamily_proto_rawDescGZIP() []byte {
	file_TagFamily_proto_rawDescOnce.Do(func() {
		file_TagFamily_proto_rawDescData = protoimpl.X.CompressGZIP(file_TagFamily_proto_rawDescData)
	})
	return file_TagFamily_proto_rawDescData
}

var file_TagFamily_proto_enumTypes = make([]protoimpl.EnumInfo, 1)
var file_TagFamily_proto_goTypes = []interface{}{
	(TagFamily)(0), // 0: fort.myrmidon.pb.TagFamily
}
var file_TagFamily_proto_depIdxs = []int32{
	0, // [0:0] is the sub-list for method output_type
	0, // [0:0] is the sub-list for method input_type
	0, // [0:0] is the sub-list for extension type_name
	0, // [0:0] is the sub-list for extension extendee
	0, // [0:0] is the sub-list for field type_name
}

func init() { file_TagFamily_proto_init() }
func file_TagFamily_proto_init() {
	if File_TagFamily_proto != nil {
		return
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_TagFamily_proto_rawDesc,
			NumEnums:      1,
			NumMessages:   0,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_TagFamily_proto_goTypes,
		DependencyIndexes: file_TagFamily_proto_depIdxs,
		EnumInfos:         file_TagFamily_proto_enumTypes,
	}.Build()
	File_TagFamily_proto = out.File
	file_TagFamily_proto_rawDesc = nil
	file_TagFamily_proto_goTypes = nil
	file_TagFamily_proto_depIdxs = nil
}