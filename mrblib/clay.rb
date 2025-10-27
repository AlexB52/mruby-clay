module Clay
  def self.ui(id = nil, **keywords)
    if id
      Clay.open_element_with_id(id)
    else
      Clay.open_element
    end

    Clay.configure_open_element(**keywords)
    yield if block_given?
    Clay.close_element
  end
end
