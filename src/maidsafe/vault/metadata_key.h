/*  Copyright 2013 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#ifndef MAIDSAFE_VAULT_GROUP_METADATA_KEY_H_
#define MAIDSAFE_VAULT_GROUP_METADATA_KEY_H_

#include <string>

#include "maidsafe/common/error.h"

#include "maidsafe/vault/metadata_key.pb.h"

namespace maidsafe {

namespace vault {

template <typename GroupName>
struct MetadataKey {
  MetadataKey();
  MetadataKey(const GroupName& group_name_in);
  explicit MetadataKey(const std::string& serialised_key);
  MetadataKey(const MetadataKey& other);
  MetadataKey(MetadataKey&& other);
  MetadataKey& operator=(MetadataKey other);
  std::string Serialise() const;

  friend bool operator==(const MetadataKey<GroupName>& lhs, const MetadataKey<GroupName>& rhs) {
    return (lhs.group_name == rhs.group_name);
  }

  GroupName group_name;
};


// Implementation

template <typename GroupName>
MetadataKey<GroupName>::MetadataKey() : group_name() {}

template <typename GroupName>
MetadataKey<GroupName>::MetadataKey(const MetadataKey& other)
    : group_name(other.group_name) {}

template <typename GroupName>
MetadataKey<GroupName>::MetadataKey(const GroupName& group_name_in)
    : group_name(group_name_in) {}

template <typename GroupName>
MetadataKey<GroupName>::MetadataKey(const std::string& serialised_key)
    : group_name() {
  protobuf::MetadataKey metadata_key_proto;
  if (!metadata_key_proto.ParseFromString(serialised_key))
    ThrowError(CommonErrors::parsing_error);
  group_name = GroupName(Identity(metadata_key_proto.group_name()));
}

template <typename GroupName>
std::string MetadataKey<GroupName>::Serialise() const {
  protobuf::MetadataKey metadata_key_proto;
  metadata_key_proto.set_group_name(group_name->string());
  return metadata_key_proto.SerializeAsString();
}

template <typename GroupName>
void swap(MetadataKey<GroupName>& lhs, MetadataKey<GroupName>& rhs) MAIDSAFE_NOEXCEPT {
  using std::swap;
  swap(lhs.group_name, rhs.group_name);
}

template <typename GroupName>
bool operator!=(const MetadataKey<GroupName>& lhs,
                const MetadataKey<GroupName>& rhs) {
  return !operator==(lhs, rhs);
}

template <typename GroupName>
bool operator<(const MetadataKey<GroupName>& lhs,
               const MetadataKey<GroupName>& rhs) {
  return lhs.group_name < rhs.group_name;
}

template <typename GroupName>
bool operator>(const MetadataKey<GroupName>& lhs, const MetadataKey<GroupName>& rhs) {
  return operator<(rhs, lhs);
}

template <typename GroupName>
bool operator<=(const MetadataKey<GroupName>& lhs, const MetadataKey<GroupName>& rhs) {
  return !operator>(lhs, rhs);
}

template <typename GroupName>
bool operator>=(const MetadataKey<GroupName>& lhs, const MetadataKey<GroupName>& rhs) {
  return !operator<(lhs, rhs);
}

}  // namespace vault

}  // namespace maidsafe

#endif  // MAIDSAFE_VAULT_GROUP_METADATA_KEY_H_
