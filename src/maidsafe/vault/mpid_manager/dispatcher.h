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

#ifndef MAIDSAFE_VAULT_MPID_MANAGER_DISPATCHER_H_
#define MAIDSAFE_VAULT_MPID_MANAGER_DISPATCHER_H_

#include <string>

#include "maidsafe/routing/routing_api.h"

#include "maidsafe/nfs/vault/messages.h"
#include "maidsafe/nfs/client/messages.h"

#include "maidsafe/vault/mpid_manager/mpid_manager.h"

namespace maidsafe {

namespace vault {

class MpidManagerDispatcher {
 public:
  explicit MpidManagerDispatcher(routing::Routing& routing);
  MpidManagerDispatcher() = delete;
  MpidManagerDispatcher(const MpidManagerDispatcher&) = delete;
  MpidManagerDispatcher(MpidManagerDispatcher&&) = delete;
  MpidManagerDispatcher& operator=(MpidManagerDispatcher) = delete;

  void SendMessageAlert(const nfs_vault::MpidMessageAlert& alert,
                        const MpidName& sender, const MpidName& receiver,
                        nfs::MessageId message_id);
  void SendMessageAlert(const nfs_vault::MpidMessageAlert& alert, const MpidName& receiver,
                        nfs::MessageId message_id);
  void SendGetMessageRequest(const nfs_vault::MpidMessageAlert& alert, const MpidName& receiver,
                             nfs::MessageId message_id);
  void SendGetMessageResponse(const DbMessageQueryResult& query_result, const MpidName& sender,
                              const MpidName& receiver, nfs::MessageId message_id);
  void SendGetMessageResponseToMpid(const nfs_client::MpidMessageOrReturnCode& response,
                                    const MpidName& receiver, nfs::MessageId message_id);

  // =========================== Sync / AccountTransfer section ====================================
  void SendSync(const MpidManager::SyncGroupKey& key, const std::string& serialised_sync);

  void SendAccountTransfer(const NodeId& destination_peer, const std::string& serialised_account);
  void SendAccountRequest(const Key& key);
  void SendAccountResponse(const std::string& serialised_account, const routing::GroupId& group_id,
                           const NodeId& sender);
  void SendDeleteRequest(const nfs_vault::MpidMessageAlert& alert, const MpidName& receiver);
  void SendMessageResponse(const MpidName& receiver, const maidsafe_error& error,
                           nfs::MessageId message_id);

 private:
  template <typename Message>
  void CheckSourcePersonaType() const;
  routing::Routing& routing_;
};

template<typename Message>
void MpidManagerDispatcher::CheckSourcePersonaType() const {
  static_assert(Message::SourcePersona::value == nfs::Persona::kMpidManager,
                "The source Persona must be kMpidManager.");
}

}  // namespace vault

}  // namespace maidsafe

#endif  // MAIDSAFE_VAULT_MPID_MANAGER_DISPATCHER_H_
