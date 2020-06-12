// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.24.0-devel
// 	protoc        v3.6.1
// source: TagStatisticsCache.proto

package fort_myrmidon_pb

import (
	proto "github.com/golang/protobuf/proto"
	timestamp "github.com/golang/protobuf/ptypes/timestamp"
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

type TagStatisticsCacheHeader struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Version uint32               `protobuf:"varint,1,opt,name=version,proto3" json:"version,omitempty"`
	Start   *timestamp.Timestamp `protobuf:"bytes,2,opt,name=start,proto3" json:"start,omitempty"`
	End     *timestamp.Timestamp `protobuf:"bytes,3,opt,name=end,proto3" json:"end,omitempty"`
}

func (x *TagStatisticsCacheHeader) Reset() {
	*x = TagStatisticsCacheHeader{}
	if protoimpl.UnsafeEnabled {
		mi := &file_TagStatisticsCache_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *TagStatisticsCacheHeader) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*TagStatisticsCacheHeader) ProtoMessage() {}

func (x *TagStatisticsCacheHeader) ProtoReflect() protoreflect.Message {
	mi := &file_TagStatisticsCache_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use TagStatisticsCacheHeader.ProtoReflect.Descriptor instead.
func (*TagStatisticsCacheHeader) Descriptor() ([]byte, []int) {
	return file_TagStatisticsCache_proto_rawDescGZIP(), []int{0}
}

func (x *TagStatisticsCacheHeader) GetVersion() uint32 {
	if x != nil {
		return x.Version
	}
	return 0
}

func (x *TagStatisticsCacheHeader) GetStart() *timestamp.Timestamp {
	if x != nil {
		return x.Start
	}
	return nil
}

func (x *TagStatisticsCacheHeader) GetEnd() *timestamp.Timestamp {
	if x != nil {
		return x.End
	}
	return nil
}

type TagStatistics struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Id           uint32               `protobuf:"varint,1,opt,name=id,proto3" json:"id,omitempty"`
	FirstSeen    *timestamp.Timestamp `protobuf:"bytes,2,opt,name=firstSeen,proto3" json:"firstSeen,omitempty"`
	LastSeen     *timestamp.Timestamp `protobuf:"bytes,3,opt,name=lastSeen,proto3" json:"lastSeen,omitempty"`
	TotalSeen    uint64               `protobuf:"varint,4,opt,name=totalSeen,proto3" json:"totalSeen,omitempty"`
	MultipleSeen uint64               `protobuf:"varint,5,opt,name=multipleSeen,proto3" json:"multipleSeen,omitempty"`
	Gap500Ms     uint64               `protobuf:"varint,6,opt,name=gap500ms,proto3" json:"gap500ms,omitempty"`
	Gap1S        uint64               `protobuf:"varint,7,opt,name=gap1s,proto3" json:"gap1s,omitempty"`
	Gap10S       uint64               `protobuf:"varint,8,opt,name=gap10s,proto3" json:"gap10s,omitempty"`
	Gap1M        uint64               `protobuf:"varint,9,opt,name=gap1m,proto3" json:"gap1m,omitempty"`
	Gap10M       uint64               `protobuf:"varint,10,opt,name=gap10m,proto3" json:"gap10m,omitempty"`
	Gap1H        uint64               `protobuf:"varint,11,opt,name=gap1h,proto3" json:"gap1h,omitempty"`
	Gap10H       uint64               `protobuf:"varint,12,opt,name=gap10h,proto3" json:"gap10h,omitempty"`
	GapMore      uint64               `protobuf:"varint,13,opt,name=gapMore,proto3" json:"gapMore,omitempty"`
}

func (x *TagStatistics) Reset() {
	*x = TagStatistics{}
	if protoimpl.UnsafeEnabled {
		mi := &file_TagStatisticsCache_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *TagStatistics) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*TagStatistics) ProtoMessage() {}

func (x *TagStatistics) ProtoReflect() protoreflect.Message {
	mi := &file_TagStatisticsCache_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use TagStatistics.ProtoReflect.Descriptor instead.
func (*TagStatistics) Descriptor() ([]byte, []int) {
	return file_TagStatisticsCache_proto_rawDescGZIP(), []int{1}
}

func (x *TagStatistics) GetId() uint32 {
	if x != nil {
		return x.Id
	}
	return 0
}

func (x *TagStatistics) GetFirstSeen() *timestamp.Timestamp {
	if x != nil {
		return x.FirstSeen
	}
	return nil
}

func (x *TagStatistics) GetLastSeen() *timestamp.Timestamp {
	if x != nil {
		return x.LastSeen
	}
	return nil
}

func (x *TagStatistics) GetTotalSeen() uint64 {
	if x != nil {
		return x.TotalSeen
	}
	return 0
}

func (x *TagStatistics) GetMultipleSeen() uint64 {
	if x != nil {
		return x.MultipleSeen
	}
	return 0
}

func (x *TagStatistics) GetGap500Ms() uint64 {
	if x != nil {
		return x.Gap500Ms
	}
	return 0
}

func (x *TagStatistics) GetGap1S() uint64 {
	if x != nil {
		return x.Gap1S
	}
	return 0
}

func (x *TagStatistics) GetGap10S() uint64 {
	if x != nil {
		return x.Gap10S
	}
	return 0
}

func (x *TagStatistics) GetGap1M() uint64 {
	if x != nil {
		return x.Gap1M
	}
	return 0
}

func (x *TagStatistics) GetGap10M() uint64 {
	if x != nil {
		return x.Gap10M
	}
	return 0
}

func (x *TagStatistics) GetGap1H() uint64 {
	if x != nil {
		return x.Gap1H
	}
	return 0
}

func (x *TagStatistics) GetGap10H() uint64 {
	if x != nil {
		return x.Gap10H
	}
	return 0
}

func (x *TagStatistics) GetGapMore() uint64 {
	if x != nil {
		return x.GapMore
	}
	return 0
}

var File_TagStatisticsCache_proto protoreflect.FileDescriptor

var file_TagStatisticsCache_proto_rawDesc = []byte{
	0x0a, 0x18, 0x54, 0x61, 0x67, 0x53, 0x74, 0x61, 0x74, 0x69, 0x73, 0x74, 0x69, 0x63, 0x73, 0x43,
	0x61, 0x63, 0x68, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x10, 0x66, 0x6f, 0x72, 0x74,
	0x2e, 0x6d, 0x79, 0x72, 0x6d, 0x69, 0x64, 0x6f, 0x6e, 0x2e, 0x70, 0x62, 0x1a, 0x1f, 0x67, 0x6f,
	0x6f, 0x67, 0x6c, 0x65, 0x2f, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62, 0x75, 0x66, 0x2f, 0x74, 0x69,
	0x6d, 0x65, 0x73, 0x74, 0x61, 0x6d, 0x70, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x22, 0x94, 0x01,
	0x0a, 0x18, 0x54, 0x61, 0x67, 0x53, 0x74, 0x61, 0x74, 0x69, 0x73, 0x74, 0x69, 0x63, 0x73, 0x43,
	0x61, 0x63, 0x68, 0x65, 0x48, 0x65, 0x61, 0x64, 0x65, 0x72, 0x12, 0x18, 0x0a, 0x07, 0x76, 0x65,
	0x72, 0x73, 0x69, 0x6f, 0x6e, 0x18, 0x01, 0x20, 0x01, 0x28, 0x0d, 0x52, 0x07, 0x76, 0x65, 0x72,
	0x73, 0x69, 0x6f, 0x6e, 0x12, 0x30, 0x0a, 0x05, 0x73, 0x74, 0x61, 0x72, 0x74, 0x18, 0x02, 0x20,
	0x01, 0x28, 0x0b, 0x32, 0x1a, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f,
	0x74, 0x6f, 0x62, 0x75, 0x66, 0x2e, 0x54, 0x69, 0x6d, 0x65, 0x73, 0x74, 0x61, 0x6d, 0x70, 0x52,
	0x05, 0x73, 0x74, 0x61, 0x72, 0x74, 0x12, 0x2c, 0x0a, 0x03, 0x65, 0x6e, 0x64, 0x18, 0x03, 0x20,
	0x01, 0x28, 0x0b, 0x32, 0x1a, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f,
	0x74, 0x6f, 0x62, 0x75, 0x66, 0x2e, 0x54, 0x69, 0x6d, 0x65, 0x73, 0x74, 0x61, 0x6d, 0x70, 0x52,
	0x03, 0x65, 0x6e, 0x64, 0x22, 0x93, 0x03, 0x0a, 0x0d, 0x54, 0x61, 0x67, 0x53, 0x74, 0x61, 0x74,
	0x69, 0x73, 0x74, 0x69, 0x63, 0x73, 0x12, 0x0e, 0x0a, 0x02, 0x69, 0x64, 0x18, 0x01, 0x20, 0x01,
	0x28, 0x0d, 0x52, 0x02, 0x69, 0x64, 0x12, 0x38, 0x0a, 0x09, 0x66, 0x69, 0x72, 0x73, 0x74, 0x53,
	0x65, 0x65, 0x6e, 0x18, 0x02, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x1a, 0x2e, 0x67, 0x6f, 0x6f, 0x67,
	0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62, 0x75, 0x66, 0x2e, 0x54, 0x69, 0x6d, 0x65,
	0x73, 0x74, 0x61, 0x6d, 0x70, 0x52, 0x09, 0x66, 0x69, 0x72, 0x73, 0x74, 0x53, 0x65, 0x65, 0x6e,
	0x12, 0x36, 0x0a, 0x08, 0x6c, 0x61, 0x73, 0x74, 0x53, 0x65, 0x65, 0x6e, 0x18, 0x03, 0x20, 0x01,
	0x28, 0x0b, 0x32, 0x1a, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x62, 0x75, 0x66, 0x2e, 0x54, 0x69, 0x6d, 0x65, 0x73, 0x74, 0x61, 0x6d, 0x70, 0x52, 0x08,
	0x6c, 0x61, 0x73, 0x74, 0x53, 0x65, 0x65, 0x6e, 0x12, 0x1c, 0x0a, 0x09, 0x74, 0x6f, 0x74, 0x61,
	0x6c, 0x53, 0x65, 0x65, 0x6e, 0x18, 0x04, 0x20, 0x01, 0x28, 0x04, 0x52, 0x09, 0x74, 0x6f, 0x74,
	0x61, 0x6c, 0x53, 0x65, 0x65, 0x6e, 0x12, 0x22, 0x0a, 0x0c, 0x6d, 0x75, 0x6c, 0x74, 0x69, 0x70,
	0x6c, 0x65, 0x53, 0x65, 0x65, 0x6e, 0x18, 0x05, 0x20, 0x01, 0x28, 0x04, 0x52, 0x0c, 0x6d, 0x75,
	0x6c, 0x74, 0x69, 0x70, 0x6c, 0x65, 0x53, 0x65, 0x65, 0x6e, 0x12, 0x1a, 0x0a, 0x08, 0x67, 0x61,
	0x70, 0x35, 0x30, 0x30, 0x6d, 0x73, 0x18, 0x06, 0x20, 0x01, 0x28, 0x04, 0x52, 0x08, 0x67, 0x61,
	0x70, 0x35, 0x30, 0x30, 0x6d, 0x73, 0x12, 0x14, 0x0a, 0x05, 0x67, 0x61, 0x70, 0x31, 0x73, 0x18,
	0x07, 0x20, 0x01, 0x28, 0x04, 0x52, 0x05, 0x67, 0x61, 0x70, 0x31, 0x73, 0x12, 0x16, 0x0a, 0x06,
	0x67, 0x61, 0x70, 0x31, 0x30, 0x73, 0x18, 0x08, 0x20, 0x01, 0x28, 0x04, 0x52, 0x06, 0x67, 0x61,
	0x70, 0x31, 0x30, 0x73, 0x12, 0x14, 0x0a, 0x05, 0x67, 0x61, 0x70, 0x31, 0x6d, 0x18, 0x09, 0x20,
	0x01, 0x28, 0x04, 0x52, 0x05, 0x67, 0x61, 0x70, 0x31, 0x6d, 0x12, 0x16, 0x0a, 0x06, 0x67, 0x61,
	0x70, 0x31, 0x30, 0x6d, 0x18, 0x0a, 0x20, 0x01, 0x28, 0x04, 0x52, 0x06, 0x67, 0x61, 0x70, 0x31,
	0x30, 0x6d, 0x12, 0x14, 0x0a, 0x05, 0x67, 0x61, 0x70, 0x31, 0x68, 0x18, 0x0b, 0x20, 0x01, 0x28,
	0x04, 0x52, 0x05, 0x67, 0x61, 0x70, 0x31, 0x68, 0x12, 0x16, 0x0a, 0x06, 0x67, 0x61, 0x70, 0x31,
	0x30, 0x68, 0x18, 0x0c, 0x20, 0x01, 0x28, 0x04, 0x52, 0x06, 0x67, 0x61, 0x70, 0x31, 0x30, 0x68,
	0x12, 0x18, 0x0a, 0x07, 0x67, 0x61, 0x70, 0x4d, 0x6f, 0x72, 0x65, 0x18, 0x0d, 0x20, 0x01, 0x28,
	0x04, 0x52, 0x07, 0x67, 0x61, 0x70, 0x4d, 0x6f, 0x72, 0x65, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x33,
}

var (
	file_TagStatisticsCache_proto_rawDescOnce sync.Once
	file_TagStatisticsCache_proto_rawDescData = file_TagStatisticsCache_proto_rawDesc
)

func file_TagStatisticsCache_proto_rawDescGZIP() []byte {
	file_TagStatisticsCache_proto_rawDescOnce.Do(func() {
		file_TagStatisticsCache_proto_rawDescData = protoimpl.X.CompressGZIP(file_TagStatisticsCache_proto_rawDescData)
	})
	return file_TagStatisticsCache_proto_rawDescData
}

var file_TagStatisticsCache_proto_msgTypes = make([]protoimpl.MessageInfo, 2)
var file_TagStatisticsCache_proto_goTypes = []interface{}{
	(*TagStatisticsCacheHeader)(nil), // 0: fort.myrmidon.pb.TagStatisticsCacheHeader
	(*TagStatistics)(nil),            // 1: fort.myrmidon.pb.TagStatistics
	(*timestamp.Timestamp)(nil),      // 2: google.protobuf.Timestamp
}
var file_TagStatisticsCache_proto_depIdxs = []int32{
	2, // 0: fort.myrmidon.pb.TagStatisticsCacheHeader.start:type_name -> google.protobuf.Timestamp
	2, // 1: fort.myrmidon.pb.TagStatisticsCacheHeader.end:type_name -> google.protobuf.Timestamp
	2, // 2: fort.myrmidon.pb.TagStatistics.firstSeen:type_name -> google.protobuf.Timestamp
	2, // 3: fort.myrmidon.pb.TagStatistics.lastSeen:type_name -> google.protobuf.Timestamp
	4, // [4:4] is the sub-list for method output_type
	4, // [4:4] is the sub-list for method input_type
	4, // [4:4] is the sub-list for extension type_name
	4, // [4:4] is the sub-list for extension extendee
	0, // [0:4] is the sub-list for field type_name
}

func init() { file_TagStatisticsCache_proto_init() }
func file_TagStatisticsCache_proto_init() {
	if File_TagStatisticsCache_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_TagStatisticsCache_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*TagStatisticsCacheHeader); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_TagStatisticsCache_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*TagStatistics); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_TagStatisticsCache_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   2,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_TagStatisticsCache_proto_goTypes,
		DependencyIndexes: file_TagStatisticsCache_proto_depIdxs,
		MessageInfos:      file_TagStatisticsCache_proto_msgTypes,
	}.Build()
	File_TagStatisticsCache_proto = out.File
	file_TagStatisticsCache_proto_rawDesc = nil
	file_TagStatisticsCache_proto_goTypes = nil
	file_TagStatisticsCache_proto_depIdxs = nil
}