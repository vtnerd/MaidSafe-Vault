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

#include "maidsafe/vault/data_manager/dispatcher.h"

namespace maidsafe {

namespace vault {

// ==================== Sync / AccountTransfer implementation ======================================
void DataManagerDispatcher::SendSync(const DataManager::Key& key,
                                     const std::string& serialised_sync) {
  typedef SynchroniseFromDataManagerToDataManager VaultMessage;
  CheckSourcePersonaType<VaultMessage>();
  SendSyncMessage(routing_, VaultMessage((nfs_vault::Content(serialised_sync))), key);
}

void DataManagerDispatcher::SendAccountTransfer(const NodeId& /*destination_peer*/,
                                                const MaidName& /*account_name*/,
                                                const std::string& /*serialised_account*/) {
  assert(0);
}

}  // namespace vault

}  // namespace maidsafe
