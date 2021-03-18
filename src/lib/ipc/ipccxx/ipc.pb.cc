// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ipc.proto

#include "ipc.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
constexpr msg_Data::msg_Data(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : dat_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , id_(PROTOBUF_LONGLONG(0)){}
struct msg_DataDefaultTypeInternal {
  constexpr msg_DataDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~msg_DataDefaultTypeInternal() {}
  union {
    msg_Data _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT msg_DataDefaultTypeInternal _msg_Data_default_instance_;
constexpr msg::msg(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_()
  , version_(PROTOBUF_LONGLONG(0))
  , length_(PROTOBUF_LONGLONG(0))
  , command_(PROTOBUF_LONGLONG(0)){}
struct msgDefaultTypeInternal {
  constexpr msgDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~msgDefaultTypeInternal() {}
  union {
    msg _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT msgDefaultTypeInternal _msg_default_instance_;
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ipc_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_ipc_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ipc_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ipc_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::msg_Data, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::msg_Data, id_),
  PROTOBUF_FIELD_OFFSET(::msg_Data, dat_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::msg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::msg, version_),
  PROTOBUF_FIELD_OFFSET(::msg, length_),
  PROTOBUF_FIELD_OFFSET(::msg, command_),
  PROTOBUF_FIELD_OFFSET(::msg, data_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::msg_Data)},
  { 7, -1, sizeof(::msg)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_msg_Data_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_msg_default_instance_),
};

const char descriptor_table_protodef_ipc_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\tipc.proto\"q\n\003msg\022\017\n\007version\030\001 \001(\003\022\016\n\006l"
  "ength\030\002 \001(\003\022\017\n\007command\030\003 \001(\003\022\027\n\004data\030\004 \003"
  "(\0132\t.msg.Data\032\037\n\004Data\022\n\n\002id\030\001 \001(\003\022\013\n\003dat"
  "\030\002 \001(\014b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ipc_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ipc_2eproto = {
  false, false, 134, descriptor_table_protodef_ipc_2eproto, "ipc.proto", 
  &descriptor_table_ipc_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_ipc_2eproto::offsets,
  file_level_metadata_ipc_2eproto, file_level_enum_descriptors_ipc_2eproto, file_level_service_descriptors_ipc_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_ipc_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_ipc_2eproto);
  return descriptor_table_ipc_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_ipc_2eproto(&descriptor_table_ipc_2eproto);

// ===================================================================

class msg_Data::_Internal {
 public:
};

msg_Data::msg_Data(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:msg.Data)
}
msg_Data::msg_Data(const msg_Data& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  dat_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_dat().empty()) {
    dat_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_dat(), 
      GetArena());
  }
  id_ = from.id_;
  // @@protoc_insertion_point(copy_constructor:msg.Data)
}

void msg_Data::SharedCtor() {
dat_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
id_ = PROTOBUF_LONGLONG(0);
}

msg_Data::~msg_Data() {
  // @@protoc_insertion_point(destructor:msg.Data)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void msg_Data::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  dat_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void msg_Data::ArenaDtor(void* object) {
  msg_Data* _this = reinterpret_cast< msg_Data* >(object);
  (void)_this;
}
void msg_Data::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void msg_Data::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void msg_Data::Clear() {
// @@protoc_insertion_point(message_clear_start:msg.Data)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  dat_.ClearToEmpty();
  id_ = PROTOBUF_LONGLONG(0);
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* msg_Data::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes dat = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_dat();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* msg_Data::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:msg.Data)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 id = 1;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(1, this->_internal_id(), target);
  }

  // bytes dat = 2;
  if (this->dat().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_dat(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg.Data)
  return target;
}

size_t msg_Data::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:msg.Data)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes dat = 2;
  if (this->dat().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_dat());
  }

  // int64 id = 1;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_id());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void msg_Data::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:msg.Data)
  GOOGLE_DCHECK_NE(&from, this);
  const msg_Data* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<msg_Data>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:msg.Data)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:msg.Data)
    MergeFrom(*source);
  }
}

void msg_Data::MergeFrom(const msg_Data& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:msg.Data)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.dat().size() > 0) {
    _internal_set_dat(from._internal_dat());
  }
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
}

void msg_Data::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:msg.Data)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void msg_Data::CopyFrom(const msg_Data& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:msg.Data)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool msg_Data::IsInitialized() const {
  return true;
}

void msg_Data::InternalSwap(msg_Data* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  dat_.Swap(&other->dat_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(id_, other->id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata msg_Data::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class msg::_Internal {
 public:
};

msg::msg(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  data_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:msg)
}
msg::msg(const msg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      data_(from.data_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&version_, &from.version_,
    static_cast<size_t>(reinterpret_cast<char*>(&command_) -
    reinterpret_cast<char*>(&version_)) + sizeof(command_));
  // @@protoc_insertion_point(copy_constructor:msg)
}

void msg::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&version_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&command_) -
    reinterpret_cast<char*>(&version_)) + sizeof(command_));
}

msg::~msg() {
  // @@protoc_insertion_point(destructor:msg)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void msg::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void msg::ArenaDtor(void* object) {
  msg* _this = reinterpret_cast< msg* >(object);
  (void)_this;
}
void msg::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void msg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void msg::Clear() {
// @@protoc_insertion_point(message_clear_start:msg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.Clear();
  ::memset(&version_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&command_) -
      reinterpret_cast<char*>(&version_)) + sizeof(command_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* msg::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int64 version = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          version_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int64 length = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          length_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int64 command = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          command_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .msg.Data data = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_data(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<34>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* msg::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:msg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 version = 1;
  if (this->version() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(1, this->_internal_version(), target);
  }

  // int64 length = 2;
  if (this->length() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(2, this->_internal_length(), target);
  }

  // int64 command = 3;
  if (this->command() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(3, this->_internal_command(), target);
  }

  // repeated .msg.Data data = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_data_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(4, this->_internal_data(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg)
  return target;
}

size_t msg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:msg)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .msg.Data data = 4;
  total_size += 1UL * this->_internal_data_size();
  for (const auto& msg : this->data_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // int64 version = 1;
  if (this->version() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_version());
  }

  // int64 length = 2;
  if (this->length() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_length());
  }

  // int64 command = 3;
  if (this->command() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_command());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void msg::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:msg)
  GOOGLE_DCHECK_NE(&from, this);
  const msg* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<msg>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:msg)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:msg)
    MergeFrom(*source);
  }
}

void msg::MergeFrom(const msg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:msg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  data_.MergeFrom(from.data_);
  if (from.version() != 0) {
    _internal_set_version(from._internal_version());
  }
  if (from.length() != 0) {
    _internal_set_length(from._internal_length());
  }
  if (from.command() != 0) {
    _internal_set_command(from._internal_command());
  }
}

void msg::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:msg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void msg::CopyFrom(const msg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:msg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool msg::IsInitialized() const {
  return true;
}

void msg::InternalSwap(msg* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  data_.InternalSwap(&other->data_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(msg, command_)
      + sizeof(msg::command_)
      - PROTOBUF_FIELD_OFFSET(msg, version_)>(
          reinterpret_cast<char*>(&version_),
          reinterpret_cast<char*>(&other->version_));
}

::PROTOBUF_NAMESPACE_ID::Metadata msg::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::msg_Data* Arena::CreateMaybeMessage< ::msg_Data >(Arena* arena) {
  return Arena::CreateMessageInternal< ::msg_Data >(arena);
}
template<> PROTOBUF_NOINLINE ::msg* Arena::CreateMaybeMessage< ::msg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::msg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
