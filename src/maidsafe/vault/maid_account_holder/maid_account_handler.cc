/***************************************************************************************************
 *  Copyright 2012 MaidSafe.net limited                                                            *
 *                                                                                                 *
 *  The following source code is property of MaidSafe.net limited and is not meant for external    *
 *  use.  The use of this code is governed by the licence file licence.txt found in the root of    *
 *  this directory and also on www.maidsafe.net.                                                   *
 *                                                                                                 *
 *  You are not free to copy, amend or otherwise use this source code without the explicit         *
 *  written permission of the board of directors of MaidSafe.net.                                  *
 **************************************************************************************************/

#include "maidsafe/vault/maid_account_holder/maid_account_handler.h"

#include "boost/filesystem/operations.hpp"

#include "maidsafe/common/error.h"
#include "maidsafe/vault/db.h"
#include "maidsafe/vault/utils.h"


namespace fs = boost::filesystem;

namespace maidsafe {

namespace vault {

MaidAccountHandler::MaidAccountHandler(Db &db, const NodeId& this_node_id)
    : db_(db),
      mutex_(),
      maid_accounts_(),
      this_node_id_(this_node_id) {}

bool MaidAccountHandler::AddAccount(std::unique_ptr<MaidAccount>&& maid_account) {
  return detail::AddAccount(mutex_, maid_accounts_, std::move(maid_account));
}

bool MaidAccountHandler::DeleteAccount(const MaidName& account_name) {
  return detail::DeleteAccount(mutex_, maid_accounts_, account_name);
}

void MaidAccountHandler::RegisterPmid(const MaidName& account_name,
                                      const nfs::PmidRegistration& pmid_registration) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto itr(detail::FindAccount(maid_accounts_, account_name));
  if (itr == maid_accounts_.end())
    ThrowError(VaultErrors::no_such_account);
  (*itr)->RegisterPmid(pmid_registration);
}

void MaidAccountHandler::UnregisterPmid(const MaidName& account_name, const PmidName& pmid_name) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto itr(detail::FindAccount(maid_accounts_, account_name));
  if (itr == maid_accounts_.end())
    ThrowError(VaultErrors::no_such_account);
  (*itr)->UnregisterPmid(pmid_name);
}

void MaidAccountHandler::UpdatePmidTotals(const MaidName& account_name,
                                          const PmidTotals& pmid_totals) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto itr(detail::FindAccount(maid_accounts_, account_name));
  if (itr == maid_accounts_.end())
    ThrowError(VaultErrors::no_such_account);
  (*itr)->UpdatePmidTotals(pmid_totals);
}

std::vector<MaidName> MaidAccountHandler::GetAccountNames() const {
  std::vector<MaidName> account_names;
  std::lock_guard<std::mutex> lock(mutex_);
  for (auto& maid_account : maid_accounts_)
    account_names.push_back(maid_account->name());
  return account_names;
}

MaidAccount::serialised_type MaidAccountHandler::GetSerialisedAccount(
    const MaidName& account_name) const {
  return detail::GetSerialisedAccount(mutex_, maid_accounts_, account_name);
}



}  // namespace vault

}  // namespace maidsafe
